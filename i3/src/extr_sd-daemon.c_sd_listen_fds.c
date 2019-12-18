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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int EINVAL ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int SD_LISTEN_FDS_START ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 unsigned long strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

int sd_listen_fds(int unset_environment) {
    int r, fd;
    const char *e;
    char *p = NULL;
    unsigned long l;

    if (!(e = getenv("LISTEN_PID"))) {
        r = 0;
        goto finish;
    }

    errno = 0;
    l = strtoul(e, &p, 10);

    if (errno != 0) {
        r = -errno;
        goto finish;
    }

    if (!p || *p || l <= 0) {
        r = -EINVAL;
        goto finish;
    }

    /* Is this for us? */
    if (getpid() != (pid_t)l) {
        r = 0;
        goto finish;
    }

    if (!(e = getenv("LISTEN_FDS"))) {
        r = 0;
        goto finish;
    }

    errno = 0;
    l = strtoul(e, &p, 10);

    if (errno != 0) {
        r = -errno;
        goto finish;
    }

    if (!p || *p) {
        r = -EINVAL;
        goto finish;
    }

    for (fd = SD_LISTEN_FDS_START; fd < SD_LISTEN_FDS_START + (int)l; fd++) {
        int flags;

        if ((flags = fcntl(fd, F_GETFD)) < 0) {
            r = -errno;
            goto finish;
        }

        if (flags & FD_CLOEXEC)
            continue;

        if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) < 0) {
            r = -errno;
            goto finish;
        }
    }

    r = (int)l;

finish:
    if (unset_environment) {
        unsetenv("LISTEN_PID");
        unsetenv("LISTEN_FDS");
    }

    return r;
}