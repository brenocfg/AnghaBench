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
struct ifmediareq {int ifm_status; int ifm_active; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int IFM_10G_T ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 

__attribute__((used)) static void
ptnet_media_status(if_t ifp, struct ifmediareq *ifmr)
{
	/* We are always active, as the backend netmap port is
	 * always open in netmap mode. */
	ifmr->ifm_status = IFM_AVALID | IFM_ACTIVE;
	ifmr->ifm_active = IFM_ETHER | IFM_10G_T | IFM_FDX;
}