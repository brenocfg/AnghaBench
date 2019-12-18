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
struct a10_aintc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_INT_IRQ_PENDING_REG (int) ; 
 int aintc_read_4 (struct a10_aintc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10_pending_irq(struct a10_aintc_softc *sc)
{
	uint32_t value;
	int i, b;

	for (i = 0; i < 3; i++) {
		value = aintc_read_4(sc, SW_INT_IRQ_PENDING_REG(i));
		if (value == 0)
			continue;
		for (b = 0; b < 32; b++)
			if (value & (1 << b)) {
				return (i * 32 + b);
			}
	}

	return (-1);
}