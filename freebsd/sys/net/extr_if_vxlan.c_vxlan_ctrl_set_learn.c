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
struct vxlan_softc {int /*<<< orphan*/  vxl_flags; } ;
struct ifvxlancmd {int vxlcmd_flags; } ;

/* Variables and functions */
 int VXLAN_CMD_FLAG_LEARN ; 
 int /*<<< orphan*/  VXLAN_FLAG_LEARN ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 

__attribute__((used)) static int
vxlan_ctrl_set_learn(struct vxlan_softc *sc, void *arg)
{
	struct ifvxlancmd *cmd;

	cmd = arg;

	VXLAN_WLOCK(sc);
	if (cmd->vxlcmd_flags & VXLAN_CMD_FLAG_LEARN)
		sc->vxl_flags |= VXLAN_FLAG_LEARN;
	else
		sc->vxl_flags &= ~VXLAN_FLAG_LEARN;
	VXLAN_WUNLOCK(sc);

	return (0);
}