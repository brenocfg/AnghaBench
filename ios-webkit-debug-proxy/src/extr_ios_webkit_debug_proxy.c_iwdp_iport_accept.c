#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  TYPE_2__* iwdp_iws_t ;
typedef  TYPE_3__* iwdp_iport_t ;
struct TYPE_11__ {int /*<<< orphan*/  ws_id_to_iws; } ;
struct TYPE_10__ {int ws_fd; int /*<<< orphan*/  ws_id; TYPE_3__* iport; } ;
struct TYPE_9__ {int /*<<< orphan*/  is_debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWDP_SUCCESS ; 
 int /*<<< orphan*/  ht_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* iwdp_iws_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_new_uuid (int /*<<< orphan*/ *) ; 

iwdp_status iwdp_iport_accept(iwdp_t self, iwdp_iport_t iport, int ws_fd,
    iwdp_iws_t *to_iws) {
  iwdp_iws_t iws = iwdp_iws_new(self->is_debug);
  iws->iport = iport;
  iws->ws_fd = ws_fd;
  rpc_new_uuid(&iws->ws_id);
  ht_put(iport->ws_id_to_iws, iws->ws_id, iws);
  *to_iws = iws;
  return IWDP_SUCCESS;
}