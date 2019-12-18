#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* va_name; int va_unit; } ;

/* Variables and functions */
 TYPE_1__** adapter ; 
 int adapters ; 
 scalar_t__ strcmp (char*,char*) ; 

int
vid_find_adapter(char *driver, int unit)
{
	int i;

	for (i = 0; i < adapters; ++i) {
		if (adapter[i] == NULL)
			continue;
		if (strcmp("*", driver) && strcmp(adapter[i]->va_name, driver))
			continue;
		if ((unit != -1) && (adapter[i]->va_unit != unit))
			continue;
		return i;
	}
	return -1;
}