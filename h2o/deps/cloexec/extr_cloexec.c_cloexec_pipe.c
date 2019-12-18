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

/* Variables and functions */
 int O_CLOEXEC ; 
 int /*<<< orphan*/  cloexec_mutex ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ set_cloexec (int) ; 

int cloexec_pipe(int fds[2])
{
#ifdef __linux__
#ifndef _GNU_SOURCE
    extern int pipe2(int pipefd[2], int flags);
#endif
    return pipe2(fds, O_CLOEXEC);
#else
    int ret = -1;
    pthread_mutex_lock(&cloexec_mutex);

    if (pipe(fds) != 0)
        goto Exit;
    if (set_cloexec(fds[0]) != 0 || set_cloexec(fds[1]) != 0)
        goto Exit;
    ret = 0;

Exit:
    pthread_mutex_unlock(&cloexec_mutex);
    return ret;
#endif
}