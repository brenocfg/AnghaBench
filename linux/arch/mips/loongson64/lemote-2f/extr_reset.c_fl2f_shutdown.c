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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DIVIL_LBAR_GPIO ; 
 int /*<<< orphan*/  DIVIL_MSR_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ GPIOL_OUT_EN ; 
 scalar_t__ GPIOL_OUT_VAL ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void fl2f_shutdown(void)
{
	u32 hi, lo, val;
	int gpio_base;

	/* get gpio base */
	_rdmsr(DIVIL_MSR_REG(DIVIL_LBAR_GPIO), &hi, &lo);
	gpio_base = lo & 0xff00;

	/* make cs5536 gpio13 output enable */
	val = inl(gpio_base + GPIOL_OUT_EN);
	val &= ~(1 << (16 + 13));
	val |= (1 << 13);
	outl(val, gpio_base + GPIOL_OUT_EN);
	mmiowb();
	/* make cs5536 gpio13 output low level voltage. */
	val = inl(gpio_base + GPIOL_OUT_VAL) & ~(1 << (13));
	val |= (1 << (16 + 13));
	outl(val, gpio_base + GPIOL_OUT_VAL);
	mmiowb();
}