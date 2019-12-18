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
 int TC_BLACK ; 
 int TC_BLUE ; 
 int TC_BROWN ; 
 int TC_CYAN ; 
 int TC_GREEN ; 
 int TC_MAGENTA ; 
 int TC_RED ; 
 int TC_WHITE ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static bool
color_name_to_teken(const char *name, int *val)
{
	if (strcasecmp(name, "black") == 0) {
		*val = TC_BLACK;
		return (true);
	}
	if (strcasecmp(name, "red") == 0) {
		*val = TC_RED;
		return (true);
	}
	if (strcasecmp(name, "green") == 0) {
		*val = TC_GREEN;
		return (true);
	}
	if (strcasecmp(name, "brown") == 0) {
		*val = TC_BROWN;
		return (true);
	}
	if (strcasecmp(name, "blue") == 0) {
		*val = TC_BLUE;
		return (true);
	}
	if (strcasecmp(name, "magenta") == 0) {
		*val = TC_MAGENTA;
		return (true);
	}
	if (strcasecmp(name, "cyan") == 0) {
		*val = TC_CYAN;
		return (true);
	}
	if (strcasecmp(name, "white") == 0) {
		*val = TC_WHITE;
		return (true);
	}
	return (false);
}