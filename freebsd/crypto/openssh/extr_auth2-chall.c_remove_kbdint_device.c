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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__** devices ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

void
remove_kbdint_device(const char *devname)
{
	int i, j;

	for (i = 0; devices[i] != NULL; i++)
		if (strcmp(devices[i]->name, devname) == 0) {
			for (j = i; devices[j] != NULL; j++)
				devices[j] = devices[j+1];
			i--;
		}
}