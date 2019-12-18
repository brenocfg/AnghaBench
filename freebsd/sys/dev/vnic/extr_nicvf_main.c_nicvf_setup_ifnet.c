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
struct nicvf {scalar_t__ hw_tso; int /*<<< orphan*/  dev; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_SCTP ; 
 int CSUM_TCP ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETHERMTU ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_HWSTATS ; 
 int IFCAP_JUMBO_MTU ; 
 int IFCAP_LRO ; 
 int IFCAP_TSO4 ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  NICVF_TSO_MAXSIZE ; 
 int /*<<< orphan*/  NICVF_TSO_NSEGS ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clearhwassist (struct ifnet*) ; 
 int /*<<< orphan*/  if_getcapabilities (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilities (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilitiesbit (struct ifnet*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenable (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setflags (struct ifnet*,int) ; 
 int /*<<< orphan*/  if_setgetcounterfn (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwassistbits (struct ifnet*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwtsomax (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwtsomaxsegcount (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwtsomaxsegsize (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setinitfn (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setioctlfn (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setmtu (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setqflushfn (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsoftc (struct ifnet*,struct nicvf*) ; 
 int /*<<< orphan*/  if_settransmitfn (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_if_getcounter ; 
 int /*<<< orphan*/  nicvf_if_init ; 
 int /*<<< orphan*/  nicvf_if_ioctl ; 
 int /*<<< orphan*/  nicvf_if_qflush ; 
 int /*<<< orphan*/  nicvf_if_transmit ; 

__attribute__((used)) static int
nicvf_setup_ifnet(struct nicvf *nic)
{
	struct ifnet *ifp;

	ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(nic->dev, "Could not allocate ifnet structure\n");
		return (ENOMEM);
	}

	nic->ifp = ifp;

	if_setsoftc(ifp, nic);
	if_initname(ifp, device_get_name(nic->dev), device_get_unit(nic->dev));
	if_setflags(ifp, IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST);

	if_settransmitfn(ifp, nicvf_if_transmit);
	if_setqflushfn(ifp, nicvf_if_qflush);
	if_setioctlfn(ifp, nicvf_if_ioctl);
	if_setinitfn(ifp, nicvf_if_init);
	if_setgetcounterfn(ifp, nicvf_if_getcounter);

	if_setmtu(ifp, ETHERMTU);

	/* Reset caps */
	if_setcapabilities(ifp, 0);

	/* Set the default values */
	if_setcapabilitiesbit(ifp, IFCAP_VLAN_MTU | IFCAP_JUMBO_MTU, 0);
	if_setcapabilitiesbit(ifp, IFCAP_LRO, 0);
	if (nic->hw_tso) {
		/* TSO */
		if_setcapabilitiesbit(ifp, IFCAP_TSO4, 0);
		/* TSO parameters */
		if_sethwtsomax(ifp, NICVF_TSO_MAXSIZE);
		if_sethwtsomaxsegcount(ifp, NICVF_TSO_NSEGS);
		if_sethwtsomaxsegsize(ifp, MCLBYTES);
	}
	/* IP/TCP/UDP HW checksums */
	if_setcapabilitiesbit(ifp, IFCAP_HWCSUM, 0);
	if_setcapabilitiesbit(ifp, IFCAP_HWSTATS, 0);
	/*
	 * HW offload enable
	 */
	if_clearhwassist(ifp);
	if_sethwassistbits(ifp, (CSUM_IP | CSUM_TCP | CSUM_UDP | CSUM_SCTP), 0);
	if (nic->hw_tso)
		if_sethwassistbits(ifp, (CSUM_TSO), 0);
	if_setcapenable(ifp, if_getcapabilities(ifp));

	return (0);
}