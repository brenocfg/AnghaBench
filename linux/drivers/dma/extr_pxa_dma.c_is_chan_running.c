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
struct pxad_phy {int dummy; } ;
struct pxad_chan {struct pxad_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCSR ; 
 int PXA_DCSR_RUN ; 
 int phy_readl_relaxed (struct pxad_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_chan_running(struct pxad_chan *chan)
{
	u32 dcsr;
	struct pxad_phy *phy = chan->phy;

	if (!phy)
		return false;
	dcsr = phy_readl_relaxed(phy, DCSR);
	return dcsr & PXA_DCSR_RUN;
}