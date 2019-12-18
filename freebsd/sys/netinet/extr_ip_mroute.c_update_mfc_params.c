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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct mfcctl2 {int* mfcc_flags; TYPE_1__ mfcc_rp; int /*<<< orphan*/ * mfcc_ttls; int /*<<< orphan*/  mfcc_parent; } ;
struct mfc {int* mfc_flags; TYPE_1__ mfc_rp; int /*<<< orphan*/ * mfc_ttls; int /*<<< orphan*/  mfc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int MRT_MFC_FLAGS_ALL ; 
 int MRT_MFC_RP ; 
 int V_mrt_api_config ; 
 int V_numvifs ; 

__attribute__((used)) static void
update_mfc_params(struct mfc *rt, struct mfcctl2 *mfccp)
{
    int i;

    rt->mfc_parent = mfccp->mfcc_parent;
    for (i = 0; i < V_numvifs; i++) {
	rt->mfc_ttls[i] = mfccp->mfcc_ttls[i];
	rt->mfc_flags[i] = mfccp->mfcc_flags[i] & V_mrt_api_config &
	    MRT_MFC_FLAGS_ALL;
    }
    /* set the RP address */
    if (V_mrt_api_config & MRT_MFC_RP)
	rt->mfc_rp = mfccp->mfcc_rp;
    else
	rt->mfc_rp.s_addr = INADDR_ANY;
}