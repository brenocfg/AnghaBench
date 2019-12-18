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
typedef  int /*<<< orphan*/  uint32_t ;
struct chipc_gpio_softc {int /*<<< orphan*/  mem_res; } ;
struct chipc_gpio_reg {int /*<<< orphan*/  value; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_GPIO_LOCK_ASSERT (struct chipc_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  bhnd_bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chipc_gpio_commit_reg(struct chipc_gpio_softc *sc, bus_size_t offset,
    struct chipc_gpio_reg *reg)
{
	uint32_t value;

	CC_GPIO_LOCK_ASSERT(sc, MA_OWNED);

	if (reg->mask == 0)
		return;

	value = bhnd_bus_read_4(sc->mem_res, offset);
	value &= ~reg->mask;
	value |= reg->value;

	bhnd_bus_write_4(sc->mem_res, offset, value);
}