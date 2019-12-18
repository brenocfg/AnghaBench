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
struct intr_irqsrc {int dummy; } ;
struct al_msix_softc {struct intr_irqsrc** isrcs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ERR_NOT_IN_MAP ; 
 int MAX_MSIX_COUNT ; 
 struct al_msix_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
al_find_intr_pos_in_map(device_t dev, struct intr_irqsrc *isrc)
{
	struct al_msix_softc *sc;
	int i;

	sc = device_get_softc(dev);
	for (i = 0; i < MAX_MSIX_COUNT; i++)
		if (sc->isrcs[i] == isrc)
			return (i);
	return (ERR_NOT_IN_MAP);
}