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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct rk_i2c_softc {int /*<<< orphan*/  sclk; } ;

/* Variables and functions */
 int RK_I2C_CLKDIVH_SHIFT ; 
 int RK_I2C_CLKDIVL_MASK ; 
 int RK_I2C_CLKDIV_MUL ; 
 int clk_get_freq (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static uint32_t
rk_i2c_get_clkdiv(struct rk_i2c_softc *sc, uint32_t speed)
{
	uint64_t sclk_freq;
	uint32_t clkdiv;
	int err;

	err = clk_get_freq(sc->sclk, &sclk_freq);
	if (err != 0)
		return (err);

	clkdiv = (sclk_freq / speed / RK_I2C_CLKDIV_MUL / 2) - 1;
	clkdiv &= RK_I2C_CLKDIVL_MASK;

	clkdiv = clkdiv << RK_I2C_CLKDIVH_SHIFT | clkdiv;

	return (clkdiv);
}