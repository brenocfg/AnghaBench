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
hci_vdata2str(int data)
{
	static char const * const	t[] = {
		/* 0x00 */ "1's complement",
		/* 0x01 */ "2's complement",
		/* 0x02 */ "Sign-Magnitude",
		/* 0x03 */ "Reserved"
	};

	return (data >= SIZE(t)? "?" : t[data]);
}