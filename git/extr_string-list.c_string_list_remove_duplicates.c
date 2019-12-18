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
struct string_list {int nr; TYPE_1__* items; scalar_t__ strdup_strings; int /*<<< orphan*/  (* cmp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  (* compare_strings_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_2__ {int /*<<< orphan*/  util; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void string_list_remove_duplicates(struct string_list *list, int free_util)
{
	if (list->nr > 1) {
		int src, dst;
		compare_strings_fn cmp = list->cmp ? list->cmp : strcmp;
		for (src = dst = 1; src < list->nr; src++) {
			if (!cmp(list->items[dst - 1].string, list->items[src].string)) {
				if (list->strdup_strings)
					free(list->items[src].string);
				if (free_util)
					free(list->items[src].util);
			} else
				list->items[dst++] = list->items[src];
		}
		list->nr = dst;
	}
}