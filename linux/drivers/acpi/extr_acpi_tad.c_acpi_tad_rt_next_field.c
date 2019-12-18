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
 scalar_t__ kstrtoint (char*,int,int*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *acpi_tad_rt_next_field(char *s, int *val)
{
	char *p;

	p = strchr(s, ':');
	if (!p)
		return NULL;

	*p = '\0';
	if (kstrtoint(s, 10, val))
		return NULL;

	return p + 1;
}