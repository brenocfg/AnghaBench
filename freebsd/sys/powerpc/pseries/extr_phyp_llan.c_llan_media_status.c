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
struct ifmediareq {int ifm_status; int /*<<< orphan*/  ifm_active; } ;

/* Variables and functions */
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_UNKNOWN ; 

__attribute__((used)) static void
llan_media_status(struct ifnet *ifp, struct ifmediareq *ifmr)
{

	ifmr->ifm_status = IFM_AVALID | IFM_ACTIVE | IFM_UNKNOWN | IFM_FDX;
	ifmr->ifm_active = IFM_ETHER;
}