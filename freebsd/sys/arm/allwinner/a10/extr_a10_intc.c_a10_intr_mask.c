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
typedef  int u_int ;
struct a10_aintc_softc {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_INT_ENABLE_REG (int) ; 
 int /*<<< orphan*/  SW_INT_MASK_REG (int) ; 
 int aintc_read_4 (struct a10_aintc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aintc_write_4 (struct a10_aintc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
a10_intr_mask(struct a10_aintc_softc *sc, u_int irq)
{
	uint32_t bit, block, value;

	bit = (irq % 32);
	block = (irq / 32);

	mtx_lock_spin(&sc->mtx);
	value = aintc_read_4(sc, SW_INT_ENABLE_REG(block));
	value &= ~(1 << bit);
	aintc_write_4(sc, SW_INT_ENABLE_REG(block), value);

	value = aintc_read_4(sc, SW_INT_MASK_REG(block));
	value |= (1 << bit);
	aintc_write_4(sc, SW_INT_MASK_REG(block), value);
	mtx_unlock_spin(&sc->mtx);
}