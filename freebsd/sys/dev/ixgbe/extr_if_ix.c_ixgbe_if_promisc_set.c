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
typedef  int u32 ;
struct ifnet {int if_flags; } ;
struct adapter {int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int IXGBE_FCTRL_MPE ; 
 int IXGBE_FCTRL_UPE ; 
 int IXGBE_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int MAX_NUM_MULTICAST_ADDRESSES ; 
 int /*<<< orphan*/  if_llmaddr_count (struct ifnet*) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ixgbe_if_promisc_set(if_ctx_t ctx, int flags)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct ifnet   *ifp = iflib_get_ifp(ctx);
	u32            rctl;
	int            mcnt = 0;

	rctl = IXGBE_READ_REG(&adapter->hw, IXGBE_FCTRL);
	rctl &= (~IXGBE_FCTRL_UPE);
	if (ifp->if_flags & IFF_ALLMULTI)
		mcnt = MAX_NUM_MULTICAST_ADDRESSES;
	else {
		mcnt = min(if_llmaddr_count(ifp), MAX_NUM_MULTICAST_ADDRESSES);
	}
	if (mcnt < MAX_NUM_MULTICAST_ADDRESSES)
		rctl &= (~IXGBE_FCTRL_MPE);
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCTRL, rctl);

	if (ifp->if_flags & IFF_PROMISC) {
		rctl |= (IXGBE_FCTRL_UPE | IXGBE_FCTRL_MPE);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCTRL, rctl);
	} else if (ifp->if_flags & IFF_ALLMULTI) {
		rctl |= IXGBE_FCTRL_MPE;
		rctl &= ~IXGBE_FCTRL_UPE;
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCTRL, rctl);
	}
	return (0);
}