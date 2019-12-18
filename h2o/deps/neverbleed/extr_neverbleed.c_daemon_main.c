#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_OPEN_MAX ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  daemon_close_notify_thread ; 
 int /*<<< orphan*/  daemon_conn_thread ; 
 int /*<<< orphan*/  dief (char*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) __attribute__((noreturn)) static void daemon_main(int listen_fd, int close_notify_fd, const char *tempdir)
{
    pthread_t tid;
    pthread_attr_t thattr;
    int sock_fd;

    { /* close all descriptors (except STDIN, STDOUT, STRERR, listen_fd, close_notify_fd) */
        int fd = (int)sysconf(_SC_OPEN_MAX) - 1;
        for (; fd > 2; --fd) {
            if (fd == listen_fd || fd == close_notify_fd)
                continue;
            close(fd);
        }
    }

    pthread_attr_init(&thattr);
    pthread_attr_setdetachstate(&thattr, 1);

    if (pthread_create(&tid, &thattr, daemon_close_notify_thread, (char *)NULL + close_notify_fd) != 0)
        dief("pthread_create failed");

    while (1) {
        while ((sock_fd = accept(listen_fd, NULL, NULL)) == -1)
            ;
        if (pthread_create(&tid, &thattr, daemon_conn_thread, (char *)NULL + sock_fd) != 0)
            dief("pthread_create failed");
    }
}