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
struct ifmediareq {int ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct ena_adapter {int /*<<< orphan*/  global_mtx; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_DBG ; 
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_LINK_UP ; 
 int /*<<< orphan*/  ENA_INFO ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_UNKNOWN ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*) ; 
 struct ena_adapter* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ena_media_status(if_t ifp, struct ifmediareq *ifmr)
{
	struct ena_adapter *adapter = if_getsoftc(ifp);
	ena_trace(ENA_DBG, "enter\n");

	mtx_lock(&adapter->global_mtx);

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (!ENA_FLAG_ISSET(ENA_FLAG_LINK_UP, adapter)) {
		mtx_unlock(&adapter->global_mtx);
		ena_trace(ENA_INFO, "Link is down\n");
		return;
	}

	ifmr->ifm_status |= IFM_ACTIVE;
	ifmr->ifm_active |= IFM_UNKNOWN | IFM_FDX;

	mtx_unlock(&adapter->global_mtx);
}