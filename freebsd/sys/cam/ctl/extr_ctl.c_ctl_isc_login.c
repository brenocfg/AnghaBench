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
struct TYPE_2__ {scalar_t__ version; scalar_t__ ha_mode; scalar_t__ ha_id; scalar_t__ max_luns; scalar_t__ max_ports; scalar_t__ max_init_per_port; } ;
union ctl_ha_msg {TYPE_1__ login; } ;
struct ctl_softc {scalar_t__ ha_mode; scalar_t__ ha_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_CHAN_CTL ; 
 scalar_t__ CTL_HA_VERSION ; 
 scalar_t__ CTL_MAX_INIT_PER_PORT ; 
 int /*<<< orphan*/  ctl_ha_msg_abort (int /*<<< orphan*/ ) ; 
 scalar_t__ ctl_max_luns ; 
 scalar_t__ ctl_max_ports ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ctl_isc_login(struct ctl_softc *softc, union ctl_ha_msg *msg, int len)
{

	if (msg->login.version != CTL_HA_VERSION) {
		printf("CTL HA peers have different versions %d != %d\n",
		    msg->login.version, CTL_HA_VERSION);
		ctl_ha_msg_abort(CTL_HA_CHAN_CTL);
		return;
	}
	if (msg->login.ha_mode != softc->ha_mode) {
		printf("CTL HA peers have different ha_mode %d != %d\n",
		    msg->login.ha_mode, softc->ha_mode);
		ctl_ha_msg_abort(CTL_HA_CHAN_CTL);
		return;
	}
	if (msg->login.ha_id == softc->ha_id) {
		printf("CTL HA peers have same ha_id %d\n", msg->login.ha_id);
		ctl_ha_msg_abort(CTL_HA_CHAN_CTL);
		return;
	}
	if (msg->login.max_luns != ctl_max_luns ||
	    msg->login.max_ports != ctl_max_ports ||
	    msg->login.max_init_per_port != CTL_MAX_INIT_PER_PORT) {
		printf("CTL HA peers have different limits\n");
		ctl_ha_msg_abort(CTL_HA_CHAN_CTL);
		return;
	}
}