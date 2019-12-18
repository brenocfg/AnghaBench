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
struct sort_list_item {struct bwstring* str; int /*<<< orphan*/  ka; } ;
struct bwstring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwsfree (struct bwstring*) ; 
 int /*<<< orphan*/  clean_keys_array (struct bwstring*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_list_item_make_key (struct sort_list_item*) ; 

void
sort_list_item_set(struct sort_list_item *si, struct bwstring *str)
{

	if (si) {
		clean_keys_array(si->str, &(si->ka));
		if (si->str) {
			if (si->str == str) {
				/* we are trying to reset the same string */
				return;
			} else {
				bwsfree(si->str);
				si->str = NULL;
			}
		}
		si->str = str;
		sort_list_item_make_key(si);
	}
}