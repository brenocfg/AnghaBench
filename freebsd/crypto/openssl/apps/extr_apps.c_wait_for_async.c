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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  SSL ;
typedef  scalar_t__ OSSL_ASYNC_FD ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (scalar_t__*) ; 
 int /*<<< orphan*/  SSL_get_all_async_fds (int /*<<< orphan*/ *,scalar_t__*,size_t*) ; 
 scalar_t__* app_malloc (int,char*) ; 
 int /*<<< orphan*/  openssl_fdset (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select (int,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void wait_for_async(SSL *s)
{
    /* On Windows select only works for sockets, so we simply don't wait  */
#ifndef OPENSSL_SYS_WINDOWS
    int width = 0;
    fd_set asyncfds;
    OSSL_ASYNC_FD *fds;
    size_t numfds;
    size_t i;

    if (!SSL_get_all_async_fds(s, NULL, &numfds))
        return;
    if (numfds == 0)
        return;
    fds = app_malloc(sizeof(OSSL_ASYNC_FD) * numfds, "allocate async fds");
    if (!SSL_get_all_async_fds(s, fds, &numfds)) {
        OPENSSL_free(fds);
        return;
    }

    FD_ZERO(&asyncfds);
    for (i = 0; i < numfds; i++) {
        if (width <= (int)fds[i])
            width = (int)fds[i] + 1;
        openssl_fdset((int)fds[i], &asyncfds);
    }
    select(width, (void *)&asyncfds, NULL, NULL, NULL);
    OPENSSL_free(fds);
#endif
}