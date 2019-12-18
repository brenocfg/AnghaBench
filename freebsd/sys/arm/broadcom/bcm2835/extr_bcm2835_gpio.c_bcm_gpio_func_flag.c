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

/* Variables and functions */
#define  BCM2835_FSEL_GPIO_IN 129 
#define  BCM2835_FSEL_GPIO_OUT 128 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 

__attribute__((used)) static uint32_t
bcm_gpio_func_flag(uint32_t nfunc)
{

	switch (nfunc) {
	case BCM2835_FSEL_GPIO_IN:
		return (GPIO_PIN_INPUT);
	case BCM2835_FSEL_GPIO_OUT:
		return (GPIO_PIN_OUTPUT);
	}
	return (0);
}