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
typedef  int uint32_t ;
struct ctl_softc {int port_min; int port_max; } ;
struct ctl_lun {int /*<<< orphan*/ ** pending_ua; int /*<<< orphan*/  lun_lock; struct ctl_softc* ctl_softc; } ;
typedef  int /*<<< orphan*/  ctl_ua_type ;

/* Variables and functions */
 int CTL_MAX_INIT_PER_PORT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ctl_clr_ua_all(struct ctl_lun *lun, uint32_t except, ctl_ua_type ua)
{
	struct ctl_softc *softc = lun->ctl_softc;
	int i, j;

	mtx_assert(&lun->lun_lock, MA_OWNED);
	for (i = softc->port_min; i < softc->port_max; i++) {
		if (lun->pending_ua[i] == NULL)
			continue;
		for (j = 0; j < CTL_MAX_INIT_PER_PORT; j++) {
			if (i * CTL_MAX_INIT_PER_PORT + j == except)
				continue;
			lun->pending_ua[i][j] &= ~ua;
		}
	}
}