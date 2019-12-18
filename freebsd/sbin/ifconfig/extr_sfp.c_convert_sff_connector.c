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

/* Variables and functions */
 int /*<<< orphan*/  conn ; 
 char* find_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static void
convert_sff_connector(char *buf, size_t size, uint8_t value)
{
	const char *x;

	if ((x = find_value(conn, value)) == NULL) {
		if (value >= 0x0D && value <= 0x1F)
			x = "Unallocated";
		else if (value >= 0x24 && value <= 0x7F)
			x = "Unallocated";
		else
			x = "Vendor specific";
	}

	snprintf(buf, size, "%s", x);
}