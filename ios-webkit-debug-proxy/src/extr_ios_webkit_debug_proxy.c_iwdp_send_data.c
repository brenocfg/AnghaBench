#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ws_t ;
typedef  int /*<<< orphan*/  ws_status ;
typedef  TYPE_3__* iwdp_t ;
typedef  TYPE_4__* iwdp_iws_t ;
struct TYPE_11__ {int /*<<< orphan*/  ws_fd; TYPE_1__* iport; } ;
struct TYPE_10__ {scalar_t__ (* send ) (TYPE_3__*,int /*<<< orphan*/ ,char const*,size_t) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* on_error ) (TYPE_2__*,char*,size_t) ;int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_3__* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  WS_SUCCESS ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char*,size_t) ; 

ws_status iwdp_send_data(ws_t ws, const char *data, size_t length) {
  iwdp_iws_t iws = (iwdp_iws_t)ws->state;
  iwdp_t self = iws->iport->self;
  return (self->send(self, iws->ws_fd, data, length) ?
      ws->on_error(ws, "Unable to send %zd bytes of data", length) :
      WS_SUCCESS);
}