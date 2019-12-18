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
typedef  unsigned long uint64_t ;
struct trapframe {int dummy; } ;
struct ps3pic_softc {unsigned long* mask_thread0; unsigned long* mask_thread1; int /*<<< orphan*/ * sc_vector; int /*<<< orphan*/ * bitmap_thread1; int /*<<< orphan*/ * bitmap_thread0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 unsigned long atomic_readandclear_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuid ; 
 struct ps3pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ffsl (unsigned long) ; 
 int /*<<< orphan*/  powerpc_dispatch_intr (int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static void
ps3pic_dispatch(device_t dev, struct trapframe *tf)
{
	uint64_t bitmap, mask;
	int irq;
	struct ps3pic_softc *sc;

	sc = device_get_softc(dev);

	if (PCPU_GET(cpuid) == 0) {
		bitmap = atomic_readandclear_64(&sc->bitmap_thread0[0]);
		mask = sc->mask_thread0[0];
	} else {
		bitmap = atomic_readandclear_64(&sc->bitmap_thread1[0]);
		mask = sc->mask_thread1[0];
	}
	powerpc_sync();

	while ((irq = ffsl(bitmap & mask) - 1) != -1) {
		bitmap &= ~(1UL << irq);
		powerpc_dispatch_intr(sc->sc_vector[63 - irq], tf);
	}
}