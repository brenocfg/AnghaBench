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
typedef  TYPE_2__* wi_t ;
typedef  int /*<<< orphan*/  wi_status ;
typedef  TYPE_3__* iwdp_t ;
typedef  TYPE_4__* iwdp_iwi_t ;
struct TYPE_11__ {int /*<<< orphan*/  wi_fd; TYPE_1__* iport; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* on_error ) (TYPE_3__*,char*,size_t) ;scalar_t__ (* send ) (TYPE_3__*,int /*<<< orphan*/ ,char const*,size_t) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_3__* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  WI_SUCCESS ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char*,size_t) ; 

wi_status iwdp_send_packet(wi_t wi, const char *packet, size_t length) {
  iwdp_iwi_t iwi = (iwdp_iwi_t)wi->state;
  iwdp_t self = iwi->iport->self;
  return (self->send(self, iwi->wi_fd, packet, length) ?
      self->on_error(self, "Unable to send %zd bytes to inspector", length) :
      WI_SUCCESS);
}