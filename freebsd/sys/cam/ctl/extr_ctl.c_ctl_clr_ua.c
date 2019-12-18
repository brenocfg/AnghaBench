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
typedef  size_t uint32_t ;
struct ctl_softc {size_t init_min; size_t init_max; } ;
struct ctl_lun {int /*<<< orphan*/ ** pending_ua; int /*<<< orphan*/  lun_lock; struct ctl_softc* ctl_softc; } ;
typedef  int /*<<< orphan*/  ctl_ua_type ;

/* Variables and functions */
 size_t CTL_MAX_INIT_PER_PORT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ctl_clr_ua(struct ctl_lun *lun, uint32_t initidx, ctl_ua_type ua)
{
	struct ctl_softc *softc = lun->ctl_softc;
	ctl_ua_type *pu;

	if (initidx < softc->init_min || initidx >= softc->init_max)
		return;
	mtx_assert(&lun->lun_lock, MA_OWNED);
	pu = lun->pending_ua[initidx / CTL_MAX_INIT_PER_PORT];
	if (pu == NULL)
		return;
	pu[initidx % CTL_MAX_INIT_PER_PORT] &= ~ua;
}