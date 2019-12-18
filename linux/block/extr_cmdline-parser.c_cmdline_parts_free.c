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
struct cmdline_parts {struct cmdline_parts* next_parts; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_subpart (struct cmdline_parts*) ; 
 int /*<<< orphan*/  kfree (struct cmdline_parts*) ; 

void cmdline_parts_free(struct cmdline_parts **parts)
{
	struct cmdline_parts *next_parts;

	while (*parts) {
		next_parts = (*parts)->next_parts;
		free_subpart(*parts);
		kfree(*parts);
		*parts = next_parts;
	}
}