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
union vxlan_sockaddr {int /*<<< orphan*/  sa; } ;
struct vxlan_softc {int /*<<< orphan*/  vxl_dst_addr; } ;
struct ifvxlancmd {union vxlan_sockaddr vxlcmd_sa; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  VXLAN_SOCKADDR_IS_IPV46 (union vxlan_sockaddr*) ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV6 (union vxlan_sockaddr*) ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 scalar_t__ vxlan_can_change_config (struct vxlan_softc*) ; 
 int vxlan_sockaddr_in6_embedscope (union vxlan_sockaddr*) ; 
 int /*<<< orphan*/  vxlan_sockaddr_in_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vxlan_ctrl_set_remote_addr(struct vxlan_softc *sc, void *arg)
{
	struct ifvxlancmd *cmd;
	union vxlan_sockaddr *vxlsa;
	int error;

	cmd = arg;
	vxlsa = &cmd->vxlcmd_sa;

	if (!VXLAN_SOCKADDR_IS_IPV46(vxlsa))
		return (EINVAL);
	if (VXLAN_SOCKADDR_IS_IPV6(vxlsa)) {
		error = vxlan_sockaddr_in6_embedscope(vxlsa);
		if (error)
			return (error);
	}

	VXLAN_WLOCK(sc);
	if (vxlan_can_change_config(sc)) {
		vxlan_sockaddr_in_copy(&sc->vxl_dst_addr, &vxlsa->sa);
		error = 0;
	} else
		error = EBUSY;
	VXLAN_WUNLOCK(sc);

	return (error);
}