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
struct sec_softc {int dummy; } ;
struct sec_desc {TYPE_1__* sd_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  shd_eu_sel1; int /*<<< orphan*/  shd_eu_sel0; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_DESC_READY2QUEUED (struct sec_softc*) ; 
 struct sec_desc* SEC_GET_READY_DESC (struct sec_softc*) ; 
 int /*<<< orphan*/  SEC_LOCK (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_PUT_BACK_READY_DESC (struct sec_softc*) ; 
 scalar_t__ SEC_READY_DESC_CNT (struct sec_softc*) ; 
 int /*<<< orphan*/  SEC_UNLOCK (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  controller ; 
 int /*<<< orphan*/  descriptors ; 
 scalar_t__ sec_enqueue_desc (struct sec_softc*,struct sec_desc*,int) ; 
 int sec_eu_channel (struct sec_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sec_enqueue(struct sec_softc *sc)
{
	struct sec_desc *desc;
	int ch0, ch1;

	SEC_LOCK(sc, descriptors);
	SEC_LOCK(sc, controller);

	while (SEC_READY_DESC_CNT(sc) > 0) {
		desc = SEC_GET_READY_DESC(sc);

		ch0 = sec_eu_channel(sc, desc->sd_desc->shd_eu_sel0);
		ch1 = sec_eu_channel(sc, desc->sd_desc->shd_eu_sel1);

		/*
		 * Both EU are used by the same channel.
		 * Enqueue descriptor in channel used by busy EUs.
		 */
		if (ch0 >= 0 && ch0 == ch1) {
			if (sec_enqueue_desc(sc, desc, ch0) >= 0) {
				SEC_DESC_READY2QUEUED(sc);
				continue;
			}
		}

		/*
		 * Only one EU is free.
		 * Enqueue descriptor in channel used by busy EU.
		 */
		if ((ch0 >= 0 && ch1 < 0) || (ch1 >= 0 && ch0 < 0)) {
			if (sec_enqueue_desc(sc, desc, (ch0 >= 0) ? ch0 : ch1)
			    >= 0) {
				SEC_DESC_READY2QUEUED(sc);
				continue;
			}
		}

		/*
		 * Both EU are free.
		 * Enqueue descriptor in first free channel.
		 */
		if (ch0 < 0 && ch1 < 0) {
			if (sec_enqueue_desc(sc, desc, -1) >= 0) {
				SEC_DESC_READY2QUEUED(sc);
				continue;
			}
		}

		/* Current descriptor can not be queued at the moment */
		SEC_PUT_BACK_READY_DESC(sc);
		break;
	}

	SEC_UNLOCK(sc, controller);
	SEC_UNLOCK(sc, descriptors);
}