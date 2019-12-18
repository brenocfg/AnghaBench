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
 int S3C2410_GPJ (int) ; 
 int S3C64XX_GPF (int) ; 

__attribute__((used)) static void camif_get_gpios(int *gpio_start, int *gpio_reset)
{
#ifdef CONFIG_ARCH_S3C24XX
	*gpio_start = S3C2410_GPJ(0);
	*gpio_reset = S3C2410_GPJ(12);
#else
	/* s3c64xx */
	*gpio_start = S3C64XX_GPF(0);
	*gpio_reset = S3C64XX_GPF(3);
#endif
}