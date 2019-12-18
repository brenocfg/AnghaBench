#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {scalar_t__ sin_port; } ;
union vxlan_sockaddr {TYPE_5__ sa; TYPE_2__ in4; } ;
struct TYPE_8__ {scalar_t__ sin_port; } ;
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct TYPE_9__ {TYPE_3__ in4; TYPE_1__ sa; } ;
struct vxlan_softc {TYPE_4__ vxl_dst_addr; } ;
struct vxlan_ftable_entry {int dummy; } ;
struct ifvxlancmd {int /*<<< orphan*/  vxlcmd_mac; union vxlan_sockaddr vxlcmd_sa; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  VXLAN_FE_FLAG_STATIC ; 
 int /*<<< orphan*/  VXLAN_SOCKADDR_IS_IPV46 (union vxlan_sockaddr*) ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV6 (union vxlan_sockaddr*) ; 
 int /*<<< orphan*/  VXLAN_WLOCK (struct vxlan_softc*) ; 
 int /*<<< orphan*/  VXLAN_WUNLOCK (struct vxlan_softc*) ; 
 struct vxlan_ftable_entry* vxlan_ftable_entry_alloc () ; 
 int /*<<< orphan*/  vxlan_ftable_entry_free (struct vxlan_ftable_entry*) ; 
 int /*<<< orphan*/  vxlan_ftable_entry_init (struct vxlan_softc*,struct vxlan_ftable_entry*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int vxlan_ftable_entry_insert (struct vxlan_softc*,struct vxlan_ftable_entry*) ; 
 int vxlan_sockaddr_in6_embedscope (union vxlan_sockaddr*) ; 
 scalar_t__ vxlan_sockaddr_in_any (union vxlan_sockaddr*) ; 
 scalar_t__ vxlan_sockaddr_in_multicast (union vxlan_sockaddr*) ; 

__attribute__((used)) static int
vxlan_ctrl_ftable_entry_add(struct vxlan_softc *sc, void *arg)
{
	union vxlan_sockaddr vxlsa;
	struct ifvxlancmd *cmd;
	struct vxlan_ftable_entry *fe;
	int error;

	cmd = arg;
	vxlsa = cmd->vxlcmd_sa;

	if (!VXLAN_SOCKADDR_IS_IPV46(&vxlsa))
		return (EINVAL);
	if (vxlan_sockaddr_in_any(&vxlsa) != 0)
		return (EINVAL);
	if (vxlan_sockaddr_in_multicast(&vxlsa) != 0)
		return (EINVAL);
	/* BMV: We could support both IPv4 and IPv6 later. */
	if (vxlsa.sa.sa_family != sc->vxl_dst_addr.sa.sa_family)
		return (EAFNOSUPPORT);

	if (VXLAN_SOCKADDR_IS_IPV6(&vxlsa)) {
		error = vxlan_sockaddr_in6_embedscope(&vxlsa);
		if (error)
			return (error);
	}

	fe = vxlan_ftable_entry_alloc();
	if (fe == NULL)
		return (ENOMEM);

	if (vxlsa.in4.sin_port == 0)
		vxlsa.in4.sin_port = sc->vxl_dst_addr.in4.sin_port;

	vxlan_ftable_entry_init(sc, fe, cmd->vxlcmd_mac, &vxlsa.sa,
	    VXLAN_FE_FLAG_STATIC);

	VXLAN_WLOCK(sc);
	error = vxlan_ftable_entry_insert(sc, fe);
	VXLAN_WUNLOCK(sc);

	if (error)
		vxlan_ftable_entry_free(fe);

	return (error);
}