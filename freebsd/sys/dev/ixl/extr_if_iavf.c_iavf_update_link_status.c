#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ixl_vsi {scalar_t__ link_active; int /*<<< orphan*/  ctx; } ;
struct iavf_sc {int /*<<< orphan*/  link_speed; scalar_t__ link_up; struct ixl_vsi vsi; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  iavf_dbg_info (struct iavf_sc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_max_vc_speed_to_value (int /*<<< orphan*/ ) ; 

void
iavf_update_link_status(struct iavf_sc *sc)
{
	struct ixl_vsi *vsi = &sc->vsi;
	u64 baudrate;

	if (sc->link_up){ 
		if (vsi->link_active == FALSE) {
			vsi->link_active = TRUE;
			baudrate = ixl_max_vc_speed_to_value(sc->link_speed);
			iavf_dbg_info(sc, "baudrate: %lu\n", baudrate);
			iflib_link_state_change(vsi->ctx, LINK_STATE_UP, baudrate);
		}
	} else { /* Link down */
		if (vsi->link_active == TRUE) {
			vsi->link_active = FALSE;
			iflib_link_state_change(vsi->ctx, LINK_STATE_DOWN, 0);
		}
	}
}