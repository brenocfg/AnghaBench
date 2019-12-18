#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_evloop_socket_t {int /*<<< orphan*/  loop; int /*<<< orphan*/  fd; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  peeraddr ;
struct TYPE_9__ {int _skip_tracing; } ;
typedef  TYPE_1__ h2o_socket_t ;
typedef  int /*<<< orphan*/  flag ;
struct TYPE_12__ {TYPE_1__ super; } ;
struct TYPE_11__ {TYPE_1__ super; } ;
struct TYPE_10__ {scalar_t__ skip_tracing; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  H2O_SOCKET_FLAG_IS_ACCEPTED_CONNECTION ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int accept4 (int /*<<< orphan*/ ,struct sockaddr*,int*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cloexec_accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 TYPE_8__* create_socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_7__* create_socket_set_nodelay (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  h2o_socket_ebpf_init_key ; 
 TYPE_3__ h2o_socket_ebpf_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_socket_setpeername (TYPE_1__*,struct sockaddr*,int) ; 

h2o_socket_t *h2o_evloop_socket_accept(h2o_socket_t *_listener)
{
    struct st_h2o_evloop_socket_t *listener = (struct st_h2o_evloop_socket_t *)_listener;
    int fd;
    h2o_socket_t *sock;

    /* cache the remote address, if we know that we are going to use the value (in h2o_socket_ebpf_lookup) */
#if h2O_USE_EBPF_MAP
    struct sockaddr_storage peeraddr[1];
    socklen_t peeraddrlen[1] = {sizeof(peeraddr[0])};
#else
    struct sockaddr_storage *peeraddr = NULL;
    socklen_t *peeraddrlen = NULL;
#endif

#if H2O_USE_ACCEPT4
    /* the anticipation here is that a socket returned by `accept4` will inherit the TCP_NODELAY flag from the listening socket */
    if ((fd = accept4(listener->fd, (struct sockaddr *)peeraddr, peeraddrlen, SOCK_NONBLOCK | SOCK_CLOEXEC)) == -1)
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
    sock = &create_socket(listener->loop, fd, H2O_SOCKET_FLAG_IS_ACCEPTED_CONNECTION)->super;
#else
    if ((fd = cloexec_accept(listener->fd, (struct sockaddr *)peeraddr, peeraddrlen)) == -1)
        return NULL;
    fcntl(fd, F_SETFL, O_NONBLOCK);
    sock = &create_socket_set_nodelay(listener->loop, fd, H2O_SOCKET_FLAG_IS_ACCEPTED_CONNECTION)->super;
#endif

    if (peeraddr != NULL && *peeraddrlen <= sizeof(*peeraddr))
        h2o_socket_setpeername(sock, (struct sockaddr *)peeraddr, *peeraddrlen);
    if (h2o_socket_ebpf_lookup(listener->loop, h2o_socket_ebpf_init_key, sock).skip_tracing)
        sock->_skip_tracing = 1;
    return sock;
}