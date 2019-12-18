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
typedef  unsigned long u_int32_t ;

/* Variables and functions */
 unsigned long NO_DISK_SECTORS ; 
 int /*<<< orphan*/  current_line_number ; 
 unsigned long secsize ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static u_int32_t
str2sectors(const char *str)
{
	char *end;
	unsigned long val;

	val = strtoul(str, &end, 0);
	if (str == end || *end == '\0') {
		warnx("ERROR line %d: unexpected size: \'%s\'",
		    current_line_number, str);
		return NO_DISK_SECTORS;
	}

	if (*end == 'K')
		val *= 1024UL / secsize;
	else if (*end == 'M')
		val *= 1024UL * 1024UL / secsize;
	else if (*end == 'G')
		val *= 1024UL * 1024UL * 1024UL / secsize;
	else {
		warnx("ERROR line %d: unexpected modifier: %c "
		    "(not K/M/G)", current_line_number, *end);
		return NO_DISK_SECTORS;
	}

	return val;
}