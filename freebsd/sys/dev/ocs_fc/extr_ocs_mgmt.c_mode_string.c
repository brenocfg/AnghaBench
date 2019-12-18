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
 int MGMT_MODE_EX ; 
 int MGMT_MODE_RD ; 
 int MGMT_MODE_WR ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static char *mode_string(int mode)
{
	static char mode_str[4];

	mode_str[0] = '\0';
	if (mode & MGMT_MODE_RD) {
		strcat(mode_str, "r");
	}
	if (mode & MGMT_MODE_WR) {
		strcat(mode_str, "w");
	}
	if (mode & MGMT_MODE_EX) {
		strcat(mode_str, "x");
	}

	return mode_str;

}