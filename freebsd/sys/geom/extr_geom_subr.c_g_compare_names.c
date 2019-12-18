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
 int g_get_device_prefix_len (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

int
g_compare_names(const char *namea, const char *nameb)
{
	int deva, devb;

	if (strcmp(namea, nameb) == 0)
		return (1);
	deva = g_get_device_prefix_len(namea);
	if (deva == 0)
		return (0);
	devb = g_get_device_prefix_len(nameb);
	if (devb == 0)
		return (0);
	if (strcmp(namea + deva, nameb + devb) == 0)
		return (1);
	return (0);
}