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

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_FSEL_ALT0 ; 
 int /*<<< orphan*/  BCM2835_FSEL_ALT1 ; 
 int /*<<< orphan*/  BCM2835_FSEL_ALT2 ; 
 int /*<<< orphan*/  BCM2835_FSEL_ALT3 ; 
 int /*<<< orphan*/  BCM2835_FSEL_ALT4 ; 
 int /*<<< orphan*/  BCM2835_FSEL_ALT5 ; 
 int /*<<< orphan*/  BCM2835_FSEL_GPIO_IN ; 
 int /*<<< orphan*/  BCM2835_FSEL_GPIO_OUT ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static int
bcm_gpio_str_func(char *func, uint32_t *nfunc)
{

	if (strcasecmp(func, "input") == 0)
		*nfunc = BCM2835_FSEL_GPIO_IN;
	else if (strcasecmp(func, "output") == 0)
		*nfunc = BCM2835_FSEL_GPIO_OUT;
	else if (strcasecmp(func, "alt0") == 0)
		*nfunc = BCM2835_FSEL_ALT0;
	else if (strcasecmp(func, "alt1") == 0)
		*nfunc = BCM2835_FSEL_ALT1;
	else if (strcasecmp(func, "alt2") == 0)
		*nfunc = BCM2835_FSEL_ALT2;
	else if (strcasecmp(func, "alt3") == 0)
		*nfunc = BCM2835_FSEL_ALT3;
	else if (strcasecmp(func, "alt4") == 0)
		*nfunc = BCM2835_FSEL_ALT4;
	else if (strcasecmp(func, "alt5") == 0)
		*nfunc = BCM2835_FSEL_ALT5;
	else
		return (-1);

	return (0);
}