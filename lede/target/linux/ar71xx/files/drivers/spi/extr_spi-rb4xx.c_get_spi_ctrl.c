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
struct rb4xx_spi {int ahb_freq; } ;

/* Variables and functions */
 int SPI_CTRL_FASTEST ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned get_spi_ctrl(struct rb4xx_spi *rbspi, unsigned hz_max,
			     const char *name)
{
	unsigned div;

	div = (rbspi->ahb_freq - 1) / (2 * hz_max);

	/*
	 * CPU has a bug at (div == 0) - first bit read is random
	 */
	if (div == 0)
		++div;

	if (name) {
		unsigned ahb_khz = (rbspi->ahb_freq + 500) / 1000;
		unsigned div_real = 2 * (div + 1);
		pr_debug("rb4xx: %s SPI clock %u kHz (AHB %u kHz / %u)\n",
		       name,
		       ahb_khz / div_real,
		       ahb_khz, div_real);
	}

	return SPI_CTRL_FASTEST + div;
}