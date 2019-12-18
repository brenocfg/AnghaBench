#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_4__ {TYPE_1__ in4; } ;
struct vxlan_softc {TYPE_2__ vxl_src_addr; } ;
struct ifvxlancmd {scalar_t__ vxlcmd_port; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 scalar_t__ vxlan_can_change_config (struct vxlan_softc*) ; 

__attribute__((used)) static int
vxlan_ctrl_set_local_port(struct vxlan_softc *sc, void *arg)
{
	struct ifvxlancmd *cmd;
	int error;

	cmd = arg;

	if (cmd->vxlcmd_port == 0)
		return (EINVAL);

	VXLAN_WLOCK(sc);
	if (vxlan_can_change_config(sc)) {
		sc->vxl_src_addr.in4.sin_port = htons(cmd->vxlcmd_port);
		error = 0;
	} else
		error = EBUSY;
	VXLAN_WUNLOCK(sc);

	return (error);
}