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
struct gic_v3_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  GICR_WAKER ; 
 int GICR_WAKER_CA ; 
 int GICR_WAKER_PS ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gic_r_read (struct gic_v3_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_r_write (struct gic_v3_softc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_redist_wake(struct gic_v3_softc *sc)
{
	uint32_t waker;
	size_t us_left = 1000000;

	waker = gic_r_read(sc, 4, GICR_WAKER);
	/* Wake up Re-Distributor for this CPU */
	waker &= ~GICR_WAKER_PS;
	gic_r_write(sc, 4, GICR_WAKER, waker);
	/*
	 * When clearing ProcessorSleep bit it is required to wait for
	 * ChildrenAsleep to become zero following the processor power-on.
	 */
	while ((gic_r_read(sc, 4, GICR_WAKER) & GICR_WAKER_CA) != 0) {
		DELAY(1);
		if (us_left-- == 0) {
			panic("Could not wake Re-Distributor for CPU%u",
			    PCPU_GET(cpuid));
		}
	}

	if (bootverbose) {
		device_printf(sc->dev, "CPU%u Re-Distributor woke up\n",
		    PCPU_GET(cpuid));
	}

	return (0);
}