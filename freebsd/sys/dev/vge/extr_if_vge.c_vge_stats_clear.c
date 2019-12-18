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
struct vge_softc {int /*<<< orphan*/  vge_dev; } ;

/* Variables and functions */
 int CSR_READ_1 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  VGE_MIBCSR ; 
 int VGE_MIBCSR_CLR ; 
 int VGE_MIBCSR_FREEZE ; 
 int VGE_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
vge_stats_clear(struct vge_softc *sc)
{
	int i;

	CSR_WRITE_1(sc, VGE_MIBCSR,
	    CSR_READ_1(sc, VGE_MIBCSR) | VGE_MIBCSR_FREEZE);
	CSR_WRITE_1(sc, VGE_MIBCSR,
	    CSR_READ_1(sc, VGE_MIBCSR) | VGE_MIBCSR_CLR);
	for (i = VGE_TIMEOUT; i > 0; i--) {
		DELAY(1);
		if ((CSR_READ_1(sc, VGE_MIBCSR) & VGE_MIBCSR_CLR) == 0)
			break;
	}
	if (i == 0)
		device_printf(sc->vge_dev, "MIB clear timed out!\n");
	CSR_WRITE_1(sc, VGE_MIBCSR, CSR_READ_1(sc, VGE_MIBCSR) &
	    ~VGE_MIBCSR_FREEZE);
}