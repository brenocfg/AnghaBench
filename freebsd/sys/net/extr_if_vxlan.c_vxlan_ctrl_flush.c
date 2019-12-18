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
struct vxlan_softc {int dummy; } ;
struct ifvxlancmd {int vxlcmd_flags; } ;

/* Variables and functions */
 int VXLAN_CMD_FLAG_FLUSH_ALL ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_ftable_flush (struct vxlan_softc*,int) ; 

__attribute__((used)) static int
vxlan_ctrl_flush(struct vxlan_softc *sc, void *arg)
{
	struct ifvxlancmd *cmd;
	int all;

	cmd = arg;
	all = cmd->vxlcmd_flags & VXLAN_CMD_FLAG_FLUSH_ALL;

	VXLAN_WLOCK(sc);
	vxlan_ftable_flush(sc, all);
	VXLAN_WUNLOCK(sc);

	return (0);
}