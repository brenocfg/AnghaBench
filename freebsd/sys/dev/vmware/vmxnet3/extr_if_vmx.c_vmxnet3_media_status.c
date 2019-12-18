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
struct vmxnet3_softc {int dummy; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AUTO ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_NONE ; 
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ vmxnet3_link_is_up (struct vmxnet3_softc*) ; 

__attribute__((used)) static void
vmxnet3_media_status(if_ctx_t ctx, struct ifmediareq * ifmr)
{
	struct vmxnet3_softc *sc;

	sc = iflib_get_softc(ctx);

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (vmxnet3_link_is_up(sc) != 0) {
		ifmr->ifm_status |= IFM_ACTIVE;
		ifmr->ifm_active |= IFM_AUTO;
	} else
		ifmr->ifm_active |= IFM_NONE;
}