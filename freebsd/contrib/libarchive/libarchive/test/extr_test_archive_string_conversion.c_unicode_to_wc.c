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
typedef  scalar_t__ wchar_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int wc_size () ; 

__attribute__((used)) static int
unicode_to_wc(wchar_t *wp, uint32_t uc)
{
	if (wc_size() == 4) {
		*wp = (wchar_t)uc;
		return (1);
	} 
	if (uc > 0xffff) {
		/* We have a code point that won't fit into a
		 * wchar_t; convert it to a surrogate pair. */
		uc -= 0x10000;
		*wp++ = (wchar_t)(((uc >> 10) & 0x3ff) + 0xD800);
		*wp = (wchar_t)((uc & 0x3ff) + 0xDC00);
		return (2);
	} else {
		*wp = (wchar_t)uc;
		return (1);
	}
}