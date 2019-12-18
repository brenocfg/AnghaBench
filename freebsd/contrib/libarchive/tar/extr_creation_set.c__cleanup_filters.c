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
struct filter_set {struct filter_set* filter_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct filter_set*) ; 

__attribute__((used)) static void
_cleanup_filters(struct filter_set *filters, int count)
{
	int i;

	for (i = 0; i < count; i++)
		free(filters[i].filter_name);
	free(filters);
}