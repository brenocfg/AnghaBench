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
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static bool
disk_match(const char *devnames, const char *disk, size_t len)
{
	const char *dname;

	dname = devnames;
	while ((dname = strstr(dname, disk)) != NULL) {
		if (dname[len] == '\0' || dname[len] == ',') {
			return (true);
		}
		dname++;
	}

	return (false);
}