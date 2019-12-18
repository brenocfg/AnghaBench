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
typedef  int cc_t ;

/* Variables and functions */
 scalar_t__ _POSIX_VDISABLE ; 

__attribute__((used)) static char *
control(cc_t c)
{
	static char buf[5];
	/*
	 * The only way I could get the Sun 3.5 compiler
	 * to shut up about
	 *	if ((unsigned int)c >= 0x80)
	 * was to assign "c" to an unsigned int variable...
	 * Arggg....
	 */
	unsigned int uic = (unsigned int)c;

	if (uic == 0x7f)
		return ("^?");
	if (c == (cc_t)_POSIX_VDISABLE) {
		return "off";
	}
	if (uic >= 0x80) {
		buf[0] = '\\';
		buf[1] = ((c>>6)&07) + '0';
		buf[2] = ((c>>3)&07) + '0';
		buf[3] = (c&07) + '0';
		buf[4] = 0;
	} else if (uic >= 0x20) {
		buf[0] = c;
		buf[1] = 0;
	} else {
		buf[0] = '^';
		buf[1] = '@'+c;
		buf[2] = 0;
	}
	return (buf);
}