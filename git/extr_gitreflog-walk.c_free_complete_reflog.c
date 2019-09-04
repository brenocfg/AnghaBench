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
struct complete_reflogs {int nr; struct complete_reflogs* ref; struct complete_reflogs* items; struct complete_reflogs* message; struct complete_reflogs* email; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct complete_reflogs*) ; 

__attribute__((used)) static void free_complete_reflog(struct complete_reflogs *array)
{
	int i;

	if (!array)
		return;

	for (i = 0; i < array->nr; i++) {
		free(array->items[i].email);
		free(array->items[i].message);
	}
	free(array->items);
	free(array->ref);
	free(array);
}