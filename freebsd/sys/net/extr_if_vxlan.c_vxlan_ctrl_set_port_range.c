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
typedef  scalar_t__ uint16_t ;
struct vxlan_softc {scalar_t__ vxl_max_port; scalar_t__ vxl_min_port; } ;
struct ifvxlancmd {scalar_t__ vxlcmd_port_min; scalar_t__ vxlcmd_port_max; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 scalar_t__ vxlan_can_change_config (struct vxlan_softc*) ; 

__attribute__((used)) static int
vxlan_ctrl_set_port_range(struct vxlan_softc *sc, void *arg)
{
	struct ifvxlancmd *cmd;
	uint16_t min, max;
	int error;

	cmd = arg;
	min = cmd->vxlcmd_port_min;
	max = cmd->vxlcmd_port_max;

	if (max < min)
		return (EINVAL);

	VXLAN_WLOCK(sc);
	if (vxlan_can_change_config(sc)) {
		sc->vxl_min_port = min;
		sc->vxl_max_port = max;
		error = 0;
	} else
		error = EBUSY;
	VXLAN_WUNLOCK(sc);

	return (error);
}