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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ixgbe_mc_addr {int dummy; } ;
struct ifnet {int if_flags; } ;
struct adapter {int /*<<< orphan*/  hw; struct ixgbe_mc_addr* mta; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  IOCTL_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int IXGBE_FCTRL_MPE ; 
 int IXGBE_FCTRL_UPE ; 
 int IXGBE_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int MAX_NUM_MULTICAST_ADDRESSES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct ixgbe_mc_addr*,int) ; 
 int if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct adapter*) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_mc_array_itr ; 
 int /*<<< orphan*/  ixgbe_mc_filter_apply ; 
 int /*<<< orphan*/  ixgbe_update_mc_addr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixgbe_if_multi_set(if_ctx_t ctx)
{
	struct adapter       *adapter = iflib_get_softc(ctx);
	struct ixgbe_mc_addr *mta;
	struct ifnet         *ifp = iflib_get_ifp(ctx);
	u8                   *update_ptr;
	u32                  fctrl;
	u_int		     mcnt;

	IOCTL_DEBUGOUT("ixgbe_if_multi_set: begin");

	mta = adapter->mta;
	bzero(mta, sizeof(*mta) * MAX_NUM_MULTICAST_ADDRESSES);

	mcnt = if_foreach_llmaddr(iflib_get_ifp(ctx), ixgbe_mc_filter_apply,
	    adapter);

	fctrl = IXGBE_READ_REG(&adapter->hw, IXGBE_FCTRL);
	fctrl |= (IXGBE_FCTRL_UPE | IXGBE_FCTRL_MPE);
	if (ifp->if_flags & IFF_PROMISC)
		fctrl |= (IXGBE_FCTRL_UPE | IXGBE_FCTRL_MPE);
	else if (mcnt >= MAX_NUM_MULTICAST_ADDRESSES ||
	    ifp->if_flags & IFF_ALLMULTI) {
		fctrl |= IXGBE_FCTRL_MPE;
		fctrl &= ~IXGBE_FCTRL_UPE;
	} else
		fctrl &= ~(IXGBE_FCTRL_UPE | IXGBE_FCTRL_MPE);

	IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCTRL, fctrl);

	if (mcnt < MAX_NUM_MULTICAST_ADDRESSES) {
		update_ptr = (u8 *)mta;
		ixgbe_update_mc_addr_list(&adapter->hw, update_ptr, mcnt,
		    ixgbe_mc_array_itr, TRUE);
	}

}