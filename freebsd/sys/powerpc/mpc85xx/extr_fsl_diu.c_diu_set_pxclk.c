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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OCP85XX_CLKDVDR ; 
 int OCP85XX_CLKDVDR_PXCKEN ; 
 int OCP85XX_CLKDVDR_PXCKINV ; 
 int OCP85XX_CLKDVDR_PXCLK_MASK ; 
 int ccsr_read4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccsr_write4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  max (unsigned long,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 unsigned long mpc85xx_get_platform_clock () ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
diu_set_pxclk(device_t dev, unsigned int freq)
{
	phandle_t node;
	unsigned long bus_freq;
	uint32_t pxclk_set;
	uint32_t clkdvd;

	node = ofw_bus_get_node(device_get_parent(dev));
	if ((bus_freq = mpc85xx_get_platform_clock()) <= 0) {
		device_printf(dev, "Unable to get bus frequency\n");
		return (ENXIO);
	}

	/* freq is in kHz */
	freq *= 1000;
	/* adding freq/2 to round-to-closest */
	pxclk_set = min(max((bus_freq + freq/2) / freq, 2), 255) << 16;
	pxclk_set |= OCP85XX_CLKDVDR_PXCKEN;
	clkdvd = ccsr_read4(OCP85XX_CLKDVDR);
	clkdvd &= ~(OCP85XX_CLKDVDR_PXCKEN | OCP85XX_CLKDVDR_PXCKINV |
		OCP85XX_CLKDVDR_PXCLK_MASK);
	ccsr_write4(OCP85XX_CLKDVDR, clkdvd);
	ccsr_write4(OCP85XX_CLKDVDR, clkdvd | pxclk_set);

	return (0);
}