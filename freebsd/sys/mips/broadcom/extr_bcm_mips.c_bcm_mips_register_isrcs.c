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
struct bcm_mips_softc {int /*<<< orphan*/  dev; TYPE_1__* isrcs; } ;
struct TYPE_2__ {size_t ivec; int /*<<< orphan*/  isrc; scalar_t__ refs; int /*<<< orphan*/ * cpuirq; } ;

/* Variables and functions */
 uintptr_t bcm_mips_pic_xref (struct bcm_mips_softc*) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  intr_isrc_deregister (int /*<<< orphan*/ *) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,uintptr_t,char*,char const*,size_t) ; 
 size_t nitems (TYPE_1__*) ; 

__attribute__((used)) static int
bcm_mips_register_isrcs(struct bcm_mips_softc *sc)
{
	const char	*name;
	uintptr_t	 xref;
	int		 error;

	xref = bcm_mips_pic_xref(sc);

	name = device_get_nameunit(sc->dev);
	for (size_t ivec = 0; ivec < nitems(sc->isrcs); ivec++) {
		sc->isrcs[ivec].ivec = ivec;
		sc->isrcs[ivec].cpuirq = NULL;
		sc->isrcs[ivec].refs = 0;

		error = intr_isrc_register(&sc->isrcs[ivec].isrc, sc->dev,
		    xref, "%s,%u", name, ivec);
		if (error) {
			for (size_t i = 0; i < ivec; i++)
				intr_isrc_deregister(&sc->isrcs[i].isrc);

			device_printf(sc->dev, "error registering IRQ %zu: "
			    "%d\n", ivec, error);
			return (error);
		}
	}

	return (0);
}