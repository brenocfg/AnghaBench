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
struct vxlan_softc {int /*<<< orphan*/  vxl_ftable_timeout; } ;
struct ifvxlancmd {int /*<<< orphan*/  vxlcmd_ftable_timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 scalar_t__ vxlan_check_ftable_timeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vxlan_ctrl_set_ftable_timeout(struct vxlan_softc *sc, void *arg)
{
	struct ifvxlancmd *cmd;
	int error;

	cmd = arg;

	VXLAN_WLOCK(sc);
	if (vxlan_check_ftable_timeout(cmd->vxlcmd_ftable_timeout) == 0) {
		sc->vxl_ftable_timeout = cmd->vxlcmd_ftable_timeout;
		error = 0;
	} else
		error = EINVAL;
	VXLAN_WUNLOCK(sc);

	return (error);
}