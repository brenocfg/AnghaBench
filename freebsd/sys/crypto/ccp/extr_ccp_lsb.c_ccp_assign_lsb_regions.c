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
typedef  unsigned long long uint64_t ;
struct ccp_softc {int valid_queues; int /*<<< orphan*/  dev; TYPE_1__* queues; } ;
struct TYPE_2__ {int private_lsb; } ;

/* Variables and functions */
 unsigned int MAX_HW_QUEUES ; 
 unsigned int MAX_LSB_REGIONS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int nitems (TYPE_1__*) ; 

void
ccp_assign_lsb_regions(struct ccp_softc *sc, uint64_t lsbmask)
{
	unsigned q, i;

	for (q = 0; q < nitems(sc->queues); q++) {
		if (((1 << q) & sc->valid_queues) == 0)
			continue;

		sc->queues[q].private_lsb = -1;

		/* Intentionally skip specialized 0th LSB */
		for (i = 1; i < MAX_LSB_REGIONS; i++) {
			if ((lsbmask &
			    (1ull << (q + (MAX_HW_QUEUES * i)))) != 0) {
				sc->queues[q].private_lsb = i;
				lsbmask &= ~(0x1Full << (MAX_HW_QUEUES * i));
				break;
			}
		}

		if (i == MAX_LSB_REGIONS) {
			device_printf(sc->dev,
			    "Ignoring queue %u with no private LSB\n", q);
			sc->valid_queues &= ~(1 << q);
		}
	}
}