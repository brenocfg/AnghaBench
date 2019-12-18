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
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int ahc_map_int (struct ahc_softc*) ; 

__attribute__((used)) static __inline int
aic7770_map_int(struct ahc_softc *ahc, int irq)
{
	/*
	 * The IRQ is unused in the FreeBSD
	 * implementation since the ISA attachment
	 * registers the IRQ with newbus before
	 * the core is called.
	 */
	return ahc_map_int(ahc);
}