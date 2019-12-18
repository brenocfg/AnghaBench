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
struct ath_tid {scalar_t__ paused; TYPE_1__* an; } ;
struct ath_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ an_leak_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TX_LOCK_ASSERT (struct ath_softc*) ; 

__attribute__((used)) static int
ath_tx_tid_can_tx_or_sched(struct ath_softc *sc, struct ath_tid *tid)
{

	ATH_TX_LOCK_ASSERT(sc);

	if (tid->an->an_leak_count > 0) {
		return (1);
	}
	if (tid->paused)
		return (0);
	return (1);
}