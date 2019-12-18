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
struct st_h2o_evloop_socket_t {int _flags; struct st_h2o_evloop_socket_t* _next_pending; TYPE_1__* loop; } ;
struct TYPE_2__ {struct st_h2o_evloop_socket_t* _pending_as_client; struct st_h2o_evloop_socket_t* _pending_as_server; } ;

/* Variables and functions */
 int H2O_SOCKET_FLAG_IS_ACCEPTED_CONNECTION ; 

void link_to_pending(struct st_h2o_evloop_socket_t *sock)
{
    if (sock->_next_pending == sock) {
        struct st_h2o_evloop_socket_t **slot = (sock->_flags & H2O_SOCKET_FLAG_IS_ACCEPTED_CONNECTION) != 0
                                                   ? &sock->loop->_pending_as_server
                                                   : &sock->loop->_pending_as_client;
        sock->_next_pending = *slot;
        *slot = sock;
    }
}