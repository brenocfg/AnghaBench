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
 int /*<<< orphan*/  __mcfgpio_ppdr (unsigned int) ; 
 int mcfgpio_bit (unsigned int) ; 
 int mcfgpio_read (int /*<<< orphan*/ ) ; 

int __mcfgpio_get_value(unsigned gpio)
{
	return mcfgpio_read(__mcfgpio_ppdr(gpio)) & mcfgpio_bit(gpio);
}