#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct flock_ {int /*<<< orphan*/  pid; int /*<<< orphan*/  len; int /*<<< orphan*/  start; int /*<<< orphan*/  whence; int /*<<< orphan*/  type; } ;
struct flock32_ {int /*<<< orphan*/  pid; int /*<<< orphan*/  len; int /*<<< orphan*/  start; int /*<<< orphan*/  whence; int /*<<< orphan*/  type; } ;
struct fdtable {int /*<<< orphan*/  cloexec; } ;
struct fd {int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  flock32 ;
typedef  int /*<<< orphan*/  flock ;
typedef  int fd_t ;
typedef  int dword_t ;
struct TYPE_2__ {struct fdtable* files; } ;

/* Variables and functions */
#define  F_DUPFD_ 139 
#define  F_DUPFD_CLOEXEC_ 138 
#define  F_GETFD_ 137 
#define  F_GETFL_ 136 
#define  F_GETLK64_ 135 
#define  F_GETLK_ 134 
#define  F_SETFD_ 133 
#define  F_SETFL_ 132 
#define  F_SETLK64_ 131 
#define  F_SETLKW64_ 130 
#define  F_SETLKW_ 129 
#define  F_SETLK_ 128 
 int /*<<< orphan*/  STRACE (char*,int,...) ; 
 int _EBADF ; 
 int _EFAULT ; 
 int _EINVAL ; 
 int /*<<< orphan*/  bit_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bit_set (int,int /*<<< orphan*/ ) ; 
 int bit_test (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct fd* f_get (int) ; 
 int f_install_start (struct fd*,int) ; 
 int fcntl_getlk (struct fd*,struct flock_*) ; 
 int fcntl_setlk (struct fd*,struct flock_*,int) ; 
 int fd_getflags (struct fd*) ; 
 int fd_setflags (struct fd*,int) ; 
 int /*<<< orphan*/  user_read (int,struct flock_*,int) ; 
 int /*<<< orphan*/  user_write (int,struct flock_*,int) ; 

dword_t sys_fcntl(fd_t f, dword_t cmd, dword_t arg) {
    struct fdtable *table = current->files;
    struct fd *fd = f_get(f);
    if (fd == NULL)
        return _EBADF;
    struct flock32_ flock32;
    struct flock_ flock;
    fd_t new_f;
    int err;
    switch (cmd) {
        case F_DUPFD_:
            STRACE("fcntl(%d, F_DUPFD, %d)", f, arg);
            fd->refcount++;
            return f_install_start(fd, arg);

        case F_DUPFD_CLOEXEC_:
            STRACE("fcntl(%d, F_DUPFD_CLOEXEC, %d)", f, arg);
            fd->refcount++;
            new_f = f_install_start(fd, arg);
            bit_set(new_f, table->cloexec);
            return new_f;

        case F_GETFD_:
            STRACE("fcntl(%d, F_GETFD)", f);
            return bit_test(f, table->cloexec);
        case F_SETFD_:
            STRACE("fcntl(%d, F_SETFD, 0x%x)", f, arg);
            if (arg & 1)
                bit_set(f, table->cloexec);
            else
                bit_clear(f, table->cloexec);
            return 0;

        case F_GETFL_:
            STRACE("fcntl(%d, F_GETFL)", f);
            return fd_getflags(fd);
        case F_SETFL_:
            STRACE("fcntl(%d, F_SETFL, %#x)", f, arg);
            return fd_setflags(fd, arg);

        case F_GETLK_:
            STRACE("fcntl(%d, F_GETLK, %#x)", f, arg);
            if (user_read(arg, &flock32, sizeof(flock32)))
                return _EFAULT;
            flock.type = flock32.type;
            flock.whence = flock32.whence;
            flock.start = flock32.start;
            flock.len = flock32.len;
            flock.pid = flock32.pid;
            err = fcntl_getlk(fd, &flock);
            if (err >= 0) {
                flock32.type = flock.type;
                flock32.whence = flock.whence;
                flock32.start = flock.start;
                flock32.len = flock.len;
                flock32.pid = flock.pid;
                if (user_write(arg, &flock32, sizeof(flock32)))
                    return _EFAULT;
            }
            return err;

        case F_GETLK64_:
            STRACE("fcntl(%d, F_GETLK64, %#x)", f, arg);
            if (user_read(arg, &flock, sizeof(flock)))
                return _EFAULT;
            err = fcntl_getlk(fd, &flock);
            if (err >= 0)
                if (user_write(arg, &flock, sizeof(flock)))
                    return _EFAULT;
            return err;

        case F_SETLK_:
        case F_SETLKW_:
            STRACE("fcntl(%d, F_SETLK%*s, %#x)", f, cmd == F_SETLKW_, "W", arg);
            if (user_read(arg, &flock32, sizeof(flock32)))
                return _EFAULT;
            flock.type = flock32.type;
            flock.whence = flock32.whence;
            flock.start = flock32.start;
            flock.len = flock32.len;
            flock.pid = flock32.pid;
            return fcntl_setlk(fd, &flock, cmd == F_SETLKW64_);

        case F_SETLK64_:
        case F_SETLKW64_:
            STRACE("fcntl(%d, F_SETLK%*s64, %#x)", f, cmd == F_SETLKW_, "W", arg);
            if (user_read(arg, &flock, sizeof(flock)))
                return _EFAULT;
            return fcntl_setlk(fd, &flock, cmd == F_SETLKW_);

        default:
            STRACE("fcntl(%d, %d)", f, cmd);
            return _EINVAL;
    }
}