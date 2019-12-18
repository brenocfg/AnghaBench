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
 int SIZE (char const* const*) ; 

char const *
hci_lmpver2str(int ver)
{
	static char const * const	t[] = {
		/* 0x00 */ "Bluetooth LMP 1.0",
		/* 0x01 */ "Bluetooth LMP 1.1",
		/* 0x02 */ "Bluetooth LMP 1.2",
		/* 0x03 */ "Bluetooth LMP 2.0",
		/* 0x04 */ "Bluetooth LMP 2.1",
		/* 0x04 */ "Bluetooth LMP 3.0",
		/* 0x04 */ "Bluetooth LMP 4.0",
		/* 0x04 */ "Bluetooth LMP 4.1",
		/* 0x04 */ "Bluetooth LMP 4.2"		
	};

	return (ver >= SIZE(t)? "?" : t[ver]);
}