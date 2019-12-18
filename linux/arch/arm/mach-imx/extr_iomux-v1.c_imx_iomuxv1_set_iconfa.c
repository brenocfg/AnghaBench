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

/* Variables and functions */
 unsigned long MXC_ICONFA1 (unsigned int) ; 
 unsigned long MXC_ICONFA2 (unsigned int) ; 
 int /*<<< orphan*/  imx_iomuxv1_rmwl (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline void imx_iomuxv1_set_iconfa(
		unsigned int port, unsigned int pin, unsigned int aout)
{
	unsigned long shift = (pin & 0xf) << 1;
	unsigned long mask = 3 << shift;
	unsigned long value = aout << shift;
	unsigned long offset = pin < 16 ? MXC_ICONFA1(port) : MXC_ICONFA2(port);

	imx_iomuxv1_rmwl(offset, mask, value);
}