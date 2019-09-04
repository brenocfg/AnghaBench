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
 int /*<<< orphan*/  free (char*) ; 

void walker_targets_free(int targets, char **target, const char **write_ref)
{
	while (targets--) {
		free(target[targets]);
		if (write_ref)
			free((char *) write_ref[targets]);
	}
}