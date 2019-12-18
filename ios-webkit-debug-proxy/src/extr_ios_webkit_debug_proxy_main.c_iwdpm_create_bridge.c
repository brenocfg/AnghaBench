#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sm_t ;
typedef  TYPE_2__* iwdpm_t ;
typedef  TYPE_3__* iwdp_t ;
struct TYPE_10__ {int /*<<< orphan*/ * is_debug; TYPE_2__* state; int /*<<< orphan*/  remove_fd; int /*<<< orphan*/  add_fd; int /*<<< orphan*/  send; int /*<<< orphan*/  connect; int /*<<< orphan*/  listen; int /*<<< orphan*/  select_port; int /*<<< orphan*/  attach; int /*<<< orphan*/  subscribe; } ;
struct TYPE_9__ {int /*<<< orphan*/  is_debug; TYPE_3__* iwdp; TYPE_1__* sm; int /*<<< orphan*/  sim_wi_socket_addr; int /*<<< orphan*/  frontend; } ;
struct TYPE_8__ {int /*<<< orphan*/ * is_debug; TYPE_2__* state; int /*<<< orphan*/  on_close; int /*<<< orphan*/  on_recv; int /*<<< orphan*/  on_sent; int /*<<< orphan*/  on_accept; } ;

/* Variables and functions */
 TYPE_3__* iwdp_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdpm_add_fd ; 
 int /*<<< orphan*/  iwdpm_attach ; 
 int /*<<< orphan*/  iwdpm_connect ; 
 int /*<<< orphan*/  iwdpm_listen ; 
 int /*<<< orphan*/  iwdpm_on_accept ; 
 int /*<<< orphan*/  iwdpm_on_close ; 
 int /*<<< orphan*/  iwdpm_on_recv ; 
 int /*<<< orphan*/  iwdpm_on_sent ; 
 int /*<<< orphan*/  iwdpm_remove_fd ; 
 int /*<<< orphan*/  iwdpm_select_port ; 
 int /*<<< orphan*/  iwdpm_send ; 
 int /*<<< orphan*/  iwdpm_subscribe ; 
 int /*<<< orphan*/  sm_free (TYPE_1__*) ; 
 TYPE_1__* sm_new (int) ; 

void iwdpm_create_bridge(iwdpm_t self) {
  sm_t sm = sm_new(4096);
  iwdp_t iwdp = iwdp_new(self->frontend, self->sim_wi_socket_addr);
  if (!sm || !iwdp) {
    sm_free(sm);
    return;
  }
  self->sm = sm;
  self->iwdp = iwdp;
  iwdp->subscribe = iwdpm_subscribe;
  iwdp->attach = iwdpm_attach;
  iwdp->select_port = iwdpm_select_port;
  iwdp->listen = iwdpm_listen;
  iwdp->connect = iwdpm_connect;
  iwdp->send = iwdpm_send;
  iwdp->add_fd = iwdpm_add_fd;
  iwdp->remove_fd = iwdpm_remove_fd;
  iwdp->state = self;
  iwdp->is_debug = &self->is_debug;
  sm->on_accept = iwdpm_on_accept;
  sm->on_sent = iwdpm_on_sent;
  sm->on_recv = iwdpm_on_recv;
  sm->on_close = iwdpm_on_close;
  sm->state = self;
  sm->is_debug = &self->is_debug;
}