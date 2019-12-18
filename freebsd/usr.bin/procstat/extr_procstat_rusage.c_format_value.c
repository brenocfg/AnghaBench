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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  HN_DECIMAL ; 
 int /*<<< orphan*/  humanize_number (char*,int,long,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long) ; 

__attribute__((used)) static const char *
format_value(long value, bool humanize, int scale)
{
	static char buffer[14];

	if (scale != 0)
		value <<= scale * 10;
	if (humanize)
		humanize_number(buffer, sizeof(buffer), value, "B",
		    scale, HN_DECIMAL);
	else
		snprintf(buffer, sizeof(buffer), "%ld   ", value);
	return (buffer);
}