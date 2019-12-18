#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int pid_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
struct TYPE_9__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ h2o_buffer_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  cloexec_mutex ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (TYPE_2__**) ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_2__**,int /*<<< orphan*/ *) ; 
 TYPE_1__ h2o_buffer_reserve (TYPE_2__**,int) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int h2o_spawnp (char const*,char**,int*,int) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int h2o_read_command(const char *cmd, char **argv, h2o_buffer_t **resp, int *child_status)
{
    int respfds[2] = {-1, -1};
    pid_t pid = -1;
    int mutex_locked = 0, ret = -1;

    h2o_buffer_init(resp, &h2o_socket_buffer_prototype);

    pthread_mutex_lock(&cloexec_mutex);
    mutex_locked = 1;

    /* create pipe for reading the result */
    if (pipe(respfds) != 0)
        goto Exit;
    if (fcntl(respfds[0], F_SETFD, O_CLOEXEC) < 0)
        goto Exit;

    /* spawn */
    int mapped_fds[] = {respfds[1], 1, /* stdout of the child process is read from the pipe */
                        -1};
    if ((pid = h2o_spawnp(cmd, argv, mapped_fds, 1)) == -1)
        goto Exit;
    close(respfds[1]);
    respfds[1] = -1;

    pthread_mutex_unlock(&cloexec_mutex);
    mutex_locked = 0;

    /* read the response from pipe */
    while (1) {
        h2o_iovec_t buf = h2o_buffer_reserve(resp, 8192);
        ssize_t r;
        while ((r = read(respfds[0], buf.base, buf.len)) == -1 && errno == EINTR)
            ;
        if (r <= 0)
            break;
        (*resp)->size += r;
    }

Exit:
    if (mutex_locked)
        pthread_mutex_unlock(&cloexec_mutex);
    if (pid != -1) {
        /* wait for the child to complete */
        pid_t r;
        while ((r = waitpid(pid, child_status, 0)) == -1 && errno == EINTR)
            ;
        if (r == pid) {
            /* success */
            ret = 0;
        }
    }
    if (respfds[0] != -1)
        close(respfds[0]);
    if (respfds[1] != -1)
        close(respfds[1]);
    if (ret != 0)
        h2o_buffer_dispose(resp);

    return ret;
}