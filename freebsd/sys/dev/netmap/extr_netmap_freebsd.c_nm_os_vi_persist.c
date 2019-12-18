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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u_char ;
struct ifnet {int if_mtu; int if_flags; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_start; scalar_t__ if_ioctl; void* if_init; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ETHERMTU ; 
 int /*<<< orphan*/  IFCAP_LINKSTATE ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_DUNIT_NONE ; 
 int /*<<< orphan*/  bcopy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,scalar_t__*) ; 
 scalar_t__ htons (int) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 
 scalar_t__ nm_vi_dummy ; 
 int nm_vi_get_index () ; 
 int /*<<< orphan*/  nm_vi_start ; 
 int /*<<< orphan*/  ticks ; 

int
nm_os_vi_persist(const char *name, struct ifnet **ret)
{
	struct ifnet *ifp;
	u_short macaddr_hi;
	uint32_t macaddr_mid;
	u_char eaddr[6];
	int unit = nm_vi_get_index(); /* just to decide MAC address */

	if (unit < 0)
		return EBUSY;
	/*
	 * We use the same MAC address generation method with tap
	 * except for the highest octet is 00:be instead of 00:bd
	 */
	macaddr_hi = htons(0x00be); /* XXX tap + 1 */
	macaddr_mid = (uint32_t) ticks;
	bcopy(&macaddr_hi, eaddr, sizeof(short));
	bcopy(&macaddr_mid, &eaddr[2], sizeof(uint32_t));
	eaddr[5] = (uint8_t)unit;

	ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		nm_prerr("if_alloc failed");
		return ENOMEM;
	}
	if_initname(ifp, name, IF_DUNIT_NONE);
	ifp->if_mtu = 65536;
	ifp->if_flags = IFF_UP | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_init = (void *)nm_vi_dummy;
	ifp->if_ioctl = nm_vi_dummy;
	ifp->if_start = nm_vi_start;
	ifp->if_mtu = ETHERMTU;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_capabilities |= IFCAP_LINKSTATE;
	ifp->if_capenable |= IFCAP_LINKSTATE;

	ether_ifattach(ifp, eaddr);
	*ret = ifp;
	return 0;
}