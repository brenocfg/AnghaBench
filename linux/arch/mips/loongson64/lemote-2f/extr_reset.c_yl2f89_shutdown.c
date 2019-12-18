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
 int LOONGSON_GPIODATA ; 
 int LOONGSON_GPIOIE ; 

__attribute__((used)) static void yl2f89_shutdown(void)
{
	/* cpu-gpio0 output low */
	LOONGSON_GPIODATA &= ~0x00000001;
	/* cpu-gpio0 as output */
	LOONGSON_GPIOIE &= ~0x00000001;
}