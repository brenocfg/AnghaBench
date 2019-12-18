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
hci_coding2str(int coding)
{
	static char const * const	t[] = {
		/* 0x00 */ "Linear",
		/* 0x01 */ "u-law",
		/* 0x02 */ "A-law",
		/* 0x03 */ "Reserved"
	};

	return (coding >= SIZE(t)? "?" : t[coding]);
}