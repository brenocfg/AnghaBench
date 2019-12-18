#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * write; } ;
struct TYPE_6__ {TYPE_2__ _cb; } ;
struct TYPE_4__ {scalar_t__ cnt; } ;
struct st_h2o_evloop_socket_t {TYPE_3__ super; TYPE_1__ _wreq; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
typedef  int /*<<< orphan*/ * h2o_socket_cb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  link_to_statechanged (struct st_h2o_evloop_socket_t*) ; 

void h2o_socket_notify_write(h2o_socket_t *_sock, h2o_socket_cb cb)
{
    struct st_h2o_evloop_socket_t *sock = (struct st_h2o_evloop_socket_t *)_sock;
    assert(sock->super._cb.write == NULL);
    assert(sock->_wreq.cnt == 0);

    sock->super._cb.write = cb;
    link_to_statechanged(sock);
}