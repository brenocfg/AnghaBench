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
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static char *
format_e3_cv (unsigned long cv, unsigned long baud, unsigned long atime)
{
	static char buf[80];
	
	if (!cv || !baud || !atime)
		sprintf (buf, "         -         ");
	else
		sprintf (buf, "%10lu (%.1e)", cv, (double)cv/baud/atime);
	return buf;
}