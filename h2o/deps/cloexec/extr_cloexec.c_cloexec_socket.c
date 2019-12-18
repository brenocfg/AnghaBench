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
 int SOCK_CLOEXEC ; 
 int /*<<< orphan*/  cloexec_mutex ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ set_cloexec (int) ; 
 int socket (int,int,int) ; 

int cloexec_socket(int domain, int type, int protocol)
{
#ifdef __linux__
    return socket(domain, type | SOCK_CLOEXEC, protocol);
#else
    int fd = -1;
    pthread_mutex_lock(&cloexec_mutex);

    if ((fd = socket(domain, type, protocol)) == -1)
        goto Exit;
    if (set_cloexec(fd) != 0) {
        close(fd);
        fd = -1;
        goto Exit;
    }

Exit:
    pthread_mutex_unlock(&cloexec_mutex);
    return fd;
#endif
}