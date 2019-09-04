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
struct st_h2o_evloop_socket_t {int /*<<< orphan*/  loop; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
struct TYPE_2__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  H2O_SOCKET_FLAG_IS_ACCEPTED_CONNECTION ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int cloexec_accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* create_socket_set_nodelay (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

h2o_socket_t *h2o_evloop_socket_accept(h2o_socket_t *_listener)
{
    struct st_h2o_evloop_socket_t *listener = (struct st_h2o_evloop_socket_t *)_listener;
    int fd;

#if H2O_USE_ACCEPT4
    /* the anticipation here is that a socket returned by `accept4` will inherit the TCP_NODELAY flag from the listening socket */
    if ((fd = accept4(listener->fd, NULL, NULL, SOCK_NONBLOCK | SOCK_CLOEXEC)) == -1)
        return NULL;
#if !defined(NDEBUG) && defined(DEBUG)
    { /* assert that TCP_NODELAY flag is inherited */
        int flag = 0;
        socklen_t len = sizeof(flag);
        if (0 == getsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, &len)) {
            assert(flag == 1);
        }
    }
#endif
    return &create_socket(listener->loop, fd, H2O_SOCKET_FLAG_IS_ACCEPTED_CONNECTION)->super;
#else
    if ((fd = cloexec_accept(listener->fd, NULL, NULL)) == -1)
        return NULL;
    fcntl(fd, F_SETFL, O_NONBLOCK);
    return &create_socket_set_nodelay(listener->loop, fd, H2O_SOCKET_FLAG_IS_ACCEPTED_CONNECTION)->super;
#endif
}