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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t SFF_8024_ID_LAST ; 
 char** sff_8024_id ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static void
convert_sff_identifier(char *buf, size_t size, uint8_t value)
{
	const char *x;

	x = NULL;
	if (value <= SFF_8024_ID_LAST)
		x = sff_8024_id[value];
	else {
		if (value > 0x80)
			x = "Vendor specific";
		else
			x = "Reserved";
	}

	snprintf(buf, size, "%s", x);
}