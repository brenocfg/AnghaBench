#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  TYPE_2__* iwdp_private_t ;
typedef  TYPE_3__* iwdp_iws_t ;
typedef  TYPE_4__* iwdp_iwi_t ;
typedef  TYPE_5__* iwdp_iport_t ;
typedef  int /*<<< orphan*/  ht_t ;
struct TYPE_18__ {char* device_id; int s_fd; scalar_t__ is_sticky; TYPE_4__* iwi; int /*<<< orphan*/  ws_id_to_iws; } ;
struct TYPE_17__ {scalar_t__ wi_fd; int /*<<< orphan*/ * iport; } ;
struct TYPE_16__ {scalar_t__ ws_fd; } ;
struct TYPE_15__ {int /*<<< orphan*/  device_id_to_iport; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* remove_fd ) (TYPE_1__*,scalar_t__) ;int /*<<< orphan*/  (* on_error ) (TYPE_1__*,char*) ;TYPE_2__* private_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWDP_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_3__**) ; 
 int /*<<< orphan*/  ht_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_get_value (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ht_remove (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ ht_values (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_iport_free (TYPE_5__*) ; 
 int /*<<< orphan*/  iwdp_log_disconnect (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,scalar_t__) ; 

iwdp_status iwdp_iport_close(iwdp_t self, iwdp_iport_t iport) {
  iwdp_private_t my = self->private_state;
  // check pointer to this iport
  const char *device_id = iport->device_id;
  ht_t iport_ht = my->device_id_to_iport;
  iwdp_iport_t old_iport = (iwdp_iport_t)ht_get_value(iport_ht, device_id);
  if (old_iport != iport) {
    return self->on_error(self, "Internal iport mismatch?");
  }
  // close clients
  iwdp_iws_t *iwss = (iwdp_iws_t *)ht_values(iport->ws_id_to_iws);
  iwdp_iws_t *iws;
  for (iws = iwss; *iws; iws++) {
    if ((*iws)->ws_fd > 0) {
      self->remove_fd(self, (*iws)->ws_fd);
    }
  }
  free(iwss);
  ht_clear(iport->ws_id_to_iws);
  // close iwi
  iwdp_iwi_t iwi = iport->iwi;
  if (iwi) {
    iwdp_log_disconnect(iport);
    iwi->iport = NULL;
    iport->iwi = NULL;
    if (iwi->wi_fd > 0) {
      self->remove_fd(self, iwi->wi_fd);
    }
  }
  if (iport->is_sticky) {
    // keep iport so we can restore the port if this device is reattached
    iport->s_fd = -1;
  } else {
    ht_remove(iport_ht, device_id);
    iwdp_iport_free(iport);
  }
  return IWDP_SUCCESS;
}