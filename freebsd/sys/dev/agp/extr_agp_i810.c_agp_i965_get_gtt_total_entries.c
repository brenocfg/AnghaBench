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
struct agp_i810_softc {int gtt_total_entries; int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I810_PGTBL_CTL ; 
#define  AGP_I810_PGTBL_SIZE_128KB 133 
#define  AGP_I810_PGTBL_SIZE_1MB 132 
#define  AGP_I810_PGTBL_SIZE_1_5MB 131 
#define  AGP_I810_PGTBL_SIZE_256KB 130 
#define  AGP_I810_PGTBL_SIZE_2MB 129 
#define  AGP_I810_PGTBL_SIZE_512KB 128 
 int AGP_I810_PGTBL_SIZE_MASK ; 
 int ENXIO ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
agp_i965_get_gtt_total_entries(device_t dev)
{
	struct agp_i810_softc *sc;
	uint32_t pgetbl_ctl;
	int error;

	sc = device_get_softc(dev);
	error = 0;
	pgetbl_ctl = bus_read_4(sc->sc_res[0], AGP_I810_PGTBL_CTL);
	switch (pgetbl_ctl & AGP_I810_PGTBL_SIZE_MASK) {
	case AGP_I810_PGTBL_SIZE_128KB:
		sc->gtt_total_entries = 128 * 1024 / 4;
		break;
	case AGP_I810_PGTBL_SIZE_256KB:
		sc->gtt_total_entries = 256 * 1024 / 4;
		break;
	case AGP_I810_PGTBL_SIZE_512KB:
		sc->gtt_total_entries = 512 * 1024 / 4;
		break;
	/* GTT pagetable sizes bigger than 512KB are not possible on G33! */
	case AGP_I810_PGTBL_SIZE_1MB:
		sc->gtt_total_entries = 1024 * 1024 / 4;
		break;
	case AGP_I810_PGTBL_SIZE_2MB:
		sc->gtt_total_entries = 2 * 1024 * 1024 / 4;
		break;
	case AGP_I810_PGTBL_SIZE_1_5MB:
		sc->gtt_total_entries = (1024 + 512) * 1024 / 4;
		break;
	default:
		device_printf(dev, "Unknown page table size\n");
		error = ENXIO;
	}
	return (error);
}