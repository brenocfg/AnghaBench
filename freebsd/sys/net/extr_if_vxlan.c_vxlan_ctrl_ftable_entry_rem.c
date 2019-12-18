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
struct vxlan_ftable_entry {int dummy; } ;
struct ifvxlancmd {int /*<<< orphan*/  vxlcmd_mac; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_ftable_entry_destroy (struct vxlan_softc*,struct vxlan_ftable_entry*) ; 
 struct vxlan_ftable_entry* vxlan_ftable_entry_lookup (struct vxlan_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vxlan_ctrl_ftable_entry_rem(struct vxlan_softc *sc, void *arg)
{
	struct ifvxlancmd *cmd;
	struct vxlan_ftable_entry *fe;
	int error;

	cmd = arg;

	VXLAN_WLOCK(sc);
	fe = vxlan_ftable_entry_lookup(sc, cmd->vxlcmd_mac);
	if (fe != NULL) {
		vxlan_ftable_entry_destroy(sc, fe);
		error = 0;
	} else
		error = ENOENT;
	VXLAN_WUNLOCK(sc);

	return (error);
}