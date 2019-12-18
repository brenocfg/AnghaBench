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
typedef  int u_int ;
struct atpic_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATPIC_MASTER ; 
 int /*<<< orphan*/  ATPIC_SLAVE ; 
 int /*<<< orphan*/  OCW2_EOI ; 
 int /*<<< orphan*/  atpic_write (struct atpic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atpic_eoi(device_t dev, u_int irq)
{
	struct atpic_softc *sc;

	sc = device_get_softc(dev);
	if (irq > 7)
		atpic_write(sc, ATPIC_SLAVE, 0, OCW2_EOI);
	atpic_write(sc, ATPIC_MASTER, 0, OCW2_EOI);
}