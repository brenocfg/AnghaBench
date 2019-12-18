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
struct string_list {int nr; TYPE_1__* items; } ;
struct rename {int /*<<< orphan*/  pair; } ;
struct TYPE_2__ {struct rename* util; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_free_filepair (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct string_list*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 

__attribute__((used)) static void final_cleanup_rename(struct string_list *rename)
{
	const struct rename *re;
	int i;

	if (rename == NULL)
		return;

	for (i = 0; i < rename->nr; i++) {
		re = rename->items[i].util;
		diff_free_filepair(re->pair);
	}
	string_list_clear(rename, 1);
	free(rename);
}