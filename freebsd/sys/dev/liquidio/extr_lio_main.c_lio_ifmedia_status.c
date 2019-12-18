#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ duplex; scalar_t__ link_up; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
struct TYPE_6__ {TYPE_2__ link; } ;
struct lio {TYPE_3__ linfo; int /*<<< orphan*/  oct_dev; } ;
struct ifnet {int dummy; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
 int /*<<< orphan*/  IFM_NONE ; 
 int /*<<< orphan*/  LIO_IFSTATE_RUNNING ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  lio_get_media_subtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_ifstate_check (struct lio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_ifmedia_status(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct lio	*lio = if_getsoftc(ifp);

	/* Report link down if the driver isn't running. */
	if (!lio_ifstate_check(lio, LIO_IFSTATE_RUNNING)) {
		ifmr->ifm_active |= IFM_NONE;
		return;
	}

	/* Setup the default interface info. */
	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (lio->linfo.link.s.link_up) {
		ifmr->ifm_status |= IFM_ACTIVE;
	} else {
		ifmr->ifm_active |= IFM_NONE;
		return;
	}

	ifmr->ifm_active |= lio_get_media_subtype(lio->oct_dev);

	if (lio->linfo.link.s.duplex)
		ifmr->ifm_active |= IFM_FDX;
	else
		ifmr->ifm_active |= IFM_HDX;
}