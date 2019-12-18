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
struct syr827_softc {TYPE_1__* reg; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ xref; } ;

/* Variables and functions */
 int ENXIO ; 
 struct syr827_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
syr827_regdev_map(device_t dev, phandle_t xref, int ncells, pcell_t *cells,
    intptr_t *num)
{
	struct syr827_softc *sc;

	sc = device_get_softc(dev);

	if (sc->reg->xref != xref)
		return (ENXIO);

	*num = 0;

	return (0);
}