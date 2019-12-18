#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  threadname ;
struct statbuf {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct sigaction_ {scalar_t__ handler; } ;
struct fd {TYPE_2__* mount; } ;
struct TYPE_9__ {char* comm; int did_exec; TYPE_3__* sighand; int /*<<< orphan*/  files; int /*<<< orphan*/  general_lock; int /*<<< orphan*/  egid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  euid; int /*<<< orphan*/  suid; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; scalar_t__ altstack; struct sigaction_* action; } ;
struct TYPE_7__ {TYPE_1__* fs; } ;
struct TYPE_6__ {int (* fstat ) (struct fd*,struct statbuf*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fd*) ; 
 int NUM_SIGS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PTR_ERR (struct fd*) ; 
 scalar_t__ SIG_DFL_ ; 
 scalar_t__ SIG_IGN_ ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int _EACCES ; 
 int _ENOEXEC ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  fd_close (struct fd*) ; 
 int /*<<< orphan*/  fdtable_do_cloexec (int /*<<< orphan*/ ) ; 
 int format_exec (struct fd*,char const*,char const*,char const*) ; 
 struct fd* generic_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setname_np (char*,...) ; 
 int shebang_exec (struct fd*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 int stub1 (struct fd*,struct statbuf*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfork_notify (TYPE_4__*) ; 

int sys_execve(const char *file, const char *argv, const char *envp) {
    struct fd *fd = generic_open(file, O_RDONLY, 0);
    if (IS_ERR(fd))
        return PTR_ERR(fd);

    struct statbuf stat;
    int err = fd->mount->fs->fstat(fd, &stat);
    if (err < 0) {
        fd_close(fd);
        return err;
    }

    // if nobody has permission to execute, it should be safe to not execute
    if (!(stat.mode & 0111)) {
        fd_close(fd);
        return _EACCES;
    }

    err = format_exec(fd, file, argv, envp);
    if (err == _ENOEXEC)
        err = shebang_exec(fd, file, argv, envp);
    fd_close(fd);
    if (err < 0)
        return err;

    // setuid/setgid
    if (stat.mode & S_ISUID) {
        current->suid = current->euid;
        current->euid = stat.uid;
    }
    if (stat.mode & S_ISGID) {
        current->sgid = current->egid;
        current->egid = stat.gid;
    }

    // save current->comm
    lock(&current->general_lock);
    const char *basename = strrchr(file, '/');
    if (basename == NULL)
        basename = file;
    else
        basename++;
    strncpy(current->comm, basename, sizeof(current->comm));
    unlock(&current->general_lock);

    // set the thread name
    char threadname[16];
    strncpy(threadname, current->comm, sizeof(threadname)-1);
    threadname[15] = '\0';
#if __APPLE__
    pthread_setname_np(threadname);
#else
    pthread_setname_np(pthread_self(), threadname);
#endif

    // cloexec
    // consider putting this in fd.c?
    fdtable_do_cloexec(current->files);

    // reset signal handlers
    lock(&current->sighand->lock);
    for (int sig = 0; sig < NUM_SIGS; sig++) {
        struct sigaction_ *action = &current->sighand->action[sig];
        if (action->handler != SIG_IGN_)
            action->handler = SIG_DFL_;
    }
    current->sighand->altstack = 0;
    unlock(&current->sighand->lock);

    current->did_exec = true;
    vfork_notify(current);
    return 0;
}