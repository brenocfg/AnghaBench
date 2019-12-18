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
struct base_data {struct base_data* base; } ;

/* Variables and functions */
 struct base_data* find_unresolved_deltas_1 (struct base_data*,struct base_data*) ; 
 int /*<<< orphan*/  free (struct base_data*) ; 

__attribute__((used)) static void find_unresolved_deltas(struct base_data *base)
{
	struct base_data *new_base, *prev_base = NULL;
	for (;;) {
		new_base = find_unresolved_deltas_1(base, prev_base);

		if (new_base) {
			prev_base = base;
			base = new_base;
		} else {
			free(base);
			base = prev_base;
			if (!base)
				return;
			prev_base = base->base;
		}
	}
}