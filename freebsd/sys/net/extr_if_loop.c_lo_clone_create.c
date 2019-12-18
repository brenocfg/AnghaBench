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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ifq_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; int if_hwassist; TYPE_1__ if_snd; int /*<<< orphan*/  if_output; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_mtu; } ;
struct if_clone {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_NULL ; 
 int ENOSPC ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_HWCSUM_IPV6 ; 
 int IFCAP_LINKSTATE ; 
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  IFT_LOOP ; 
 int /*<<< orphan*/  LOMTU ; 
 int LO_CSUM_FEATURES ; 
 int LO_CSUM_FEATURES6 ; 
 struct ifnet* V_loif ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  loioctl ; 
 int /*<<< orphan*/  loname ; 
 int /*<<< orphan*/  looutput ; 

__attribute__((used)) static int
lo_clone_create(struct if_clone *ifc, int unit, caddr_t params)
{
	struct ifnet *ifp;

	ifp = if_alloc(IFT_LOOP);
	if (ifp == NULL)
		return (ENOSPC);

	if_initname(ifp, loname, unit);
	ifp->if_mtu = LOMTU;
	ifp->if_flags = IFF_LOOPBACK | IFF_MULTICAST;
	ifp->if_ioctl = loioctl;
	ifp->if_output = looutput;
	ifp->if_snd.ifq_maxlen = ifqmaxlen;
	ifp->if_capabilities = ifp->if_capenable =
	    IFCAP_HWCSUM | IFCAP_HWCSUM_IPV6 | IFCAP_LINKSTATE;
	ifp->if_hwassist = LO_CSUM_FEATURES | LO_CSUM_FEATURES6;
	if_attach(ifp);
	bpfattach(ifp, DLT_NULL, sizeof(u_int32_t));
	if (V_loif == NULL)
		V_loif = ifp;

	return (0);
}