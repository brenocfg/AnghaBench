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
typedef  int /*<<< orphan*/  u32 ;
struct ifnet {int dummy; } ;
struct adapter {int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RCTL ; 
 int /*<<< orphan*/  E1000_RCTL_MPE ; 
 int /*<<< orphan*/  E1000_RCTL_SBP ; 
 int /*<<< orphan*/  E1000_RCTL_UPE ; 
 int /*<<< orphan*/  E1000_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_ALLMULTI ; 
 int MAX_NUM_MULTICAST_ADDRESSES ; 
 int if_getflags (struct ifnet*) ; 
 int if_llmaddr_count (struct ifnet*) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_disable_promisc(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct ifnet *ifp = iflib_get_ifp(ctx);
	u32 reg_rctl;
	int mcnt = 0;

	reg_rctl = E1000_READ_REG(&adapter->hw, E1000_RCTL);
	reg_rctl &= (~E1000_RCTL_UPE);
	if (if_getflags(ifp) & IFF_ALLMULTI)
		mcnt = MAX_NUM_MULTICAST_ADDRESSES;
	else
		mcnt = if_llmaddr_count(ifp);
	/* Don't disable if in MAX groups */
	if (mcnt < MAX_NUM_MULTICAST_ADDRESSES)
		reg_rctl &=  (~E1000_RCTL_MPE);
	reg_rctl &=  (~E1000_RCTL_SBP);
	E1000_WRITE_REG(&adapter->hw, E1000_RCTL, reg_rctl);
}