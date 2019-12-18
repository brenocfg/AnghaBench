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

__attribute__((used)) static size_t
str_strip(
	const char ** 	datap,
	size_t		len
	)
{
	static const char empty[] = "";
	
	if (*datap && len) {
		const char * cpl = *datap;
		const char * cpr = cpl + len;
		
		while (cpl != cpr && *(const unsigned char*)cpl <= ' ')
			++cpl;
		while (cpl != cpr && *(const unsigned char*)(cpr - 1) <= ' ')
			--cpr;
		*datap = cpl;		
		len = (size_t)(cpr - cpl);
	} else {
		*datap = empty;
		len = 0;
	}
	return len;
}