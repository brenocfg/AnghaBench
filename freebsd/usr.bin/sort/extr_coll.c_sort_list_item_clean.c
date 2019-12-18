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
struct sort_list_item {int /*<<< orphan*/ * str; int /*<<< orphan*/  ka; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwsfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_keys_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
sort_list_item_clean(struct sort_list_item *si)
{

	if (si) {
		clean_keys_array(si->str, &(si->ka));
		if (si->str) {
			bwsfree(si->str);
			si->str = NULL;
		}
	}
}