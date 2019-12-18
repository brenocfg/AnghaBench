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
struct ifnet {int dummy; } ;
struct ifmediareq {int ifm_status; int ifm_active; } ;

/* Variables and functions */
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_MANUAL ; 

__attribute__((used)) static void
xn_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{

	ifmr->ifm_status = IFM_AVALID|IFM_ACTIVE;
	ifmr->ifm_active = IFM_ETHER|IFM_MANUAL;
}