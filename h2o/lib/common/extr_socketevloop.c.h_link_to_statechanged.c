#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_evloop_socket_t {struct st_h2o_evloop_socket_t* _next_statechanged; TYPE_2__* loop; } ;
struct TYPE_3__ {struct st_h2o_evloop_socket_t** tail_ref; } ;
struct TYPE_4__ {TYPE_1__ _statechanged; } ;

/* Variables and functions */

__attribute__((used)) static void link_to_statechanged(struct st_h2o_evloop_socket_t *sock)
{
    if (sock->_next_statechanged == sock) {
        sock->_next_statechanged = NULL;
        *sock->loop->_statechanged.tail_ref = sock;
        sock->loop->_statechanged.tail_ref = &sock->_next_statechanged;
    }
}