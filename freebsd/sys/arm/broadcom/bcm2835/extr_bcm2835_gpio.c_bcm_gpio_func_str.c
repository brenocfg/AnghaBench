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
#define  BCM2835_FSEL_ALT0 135 
#define  BCM2835_FSEL_ALT1 134 
#define  BCM2835_FSEL_ALT2 133 
#define  BCM2835_FSEL_ALT3 132 
#define  BCM2835_FSEL_ALT4 131 
#define  BCM2835_FSEL_ALT5 130 
#define  BCM2835_FSEL_GPIO_IN 129 
#define  BCM2835_FSEL_GPIO_OUT 128 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
bcm_gpio_func_str(uint32_t nfunc, char *buf, int bufsize)
{

	switch (nfunc) {
	case BCM2835_FSEL_GPIO_IN:
		strncpy(buf, "input", bufsize);
		break;
	case BCM2835_FSEL_GPIO_OUT:
		strncpy(buf, "output", bufsize);
		break;
	case BCM2835_FSEL_ALT0:
		strncpy(buf, "alt0", bufsize);
		break;
	case BCM2835_FSEL_ALT1:
		strncpy(buf, "alt1", bufsize);
		break;
	case BCM2835_FSEL_ALT2:
		strncpy(buf, "alt2", bufsize);
		break;
	case BCM2835_FSEL_ALT3:
		strncpy(buf, "alt3", bufsize);
		break;
	case BCM2835_FSEL_ALT4:
		strncpy(buf, "alt4", bufsize);
		break;
	case BCM2835_FSEL_ALT5:
		strncpy(buf, "alt5", bufsize);
		break;
	default:
		strncpy(buf, "invalid", bufsize);
	}
}