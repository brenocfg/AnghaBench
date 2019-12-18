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
typedef  int uint8_t ;
typedef  void* device_t ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (void*,char*,int) ; 
 int superio_read (void*,int) ; 
 int /*<<< orphan*/  superio_write (void*,int,int) ; 

__attribute__((used)) static void
itwd_intr(void *cookie)
{
	device_t dev = cookie;
	uint8_t val;

	val = superio_read(dev, 0x71);
	if (bootverbose)
		device_printf(dev, "got interrupt, wdt status = %d\n", val & 1);
	superio_write(dev, 0x71, val & ~((uint8_t)0x01));
}