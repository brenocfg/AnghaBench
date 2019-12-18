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
typedef  scalar_t__ uint8_t ;
struct twl_clks_softc {int /*<<< orphan*/  sc_pdev; } ;
struct twl_clk_entry {scalar_t__ reg_off; int /*<<< orphan*/  sub_dev; } ;

/* Variables and functions */
 int twl_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static inline int
twl_clks_write_1(struct twl_clks_softc *sc, struct twl_clk_entry *clk,
	uint8_t off, uint8_t val)
{
	return (twl_write(sc->sc_pdev, clk->sub_dev, clk->reg_off + off, &val, 1));
}