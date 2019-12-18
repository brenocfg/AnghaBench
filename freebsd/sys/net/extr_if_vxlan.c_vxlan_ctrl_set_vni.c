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
struct vxlan_softc {int /*<<< orphan*/  vxl_vni; } ;
struct ifvxlancmd {int /*<<< orphan*/  vxlcmd_vni; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 scalar_t__ vxlan_can_change_config (struct vxlan_softc*) ; 
 scalar_t__ vxlan_check_vni (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vxlan_ctrl_set_vni(struct vxlan_softc *sc, void *arg)
{
	struct ifvxlancmd *cmd;
	int error;

	cmd = arg;

	if (vxlan_check_vni(cmd->vxlcmd_vni) != 0)
		return (EINVAL);

	VXLAN_WLOCK(sc);
	if (vxlan_can_change_config(sc)) {
		sc->vxl_vni = cmd->vxlcmd_vni;
		error = 0;
	} else
		error = EBUSY;
	VXLAN_WUNLOCK(sc);

	return (error);
}