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
struct sort_list_item {int /*<<< orphan*/  str; } ;
struct sort_list {size_t count; struct sort_list_item** list; } ;
struct TYPE_2__ {int /*<<< orphan*/  zflag; int /*<<< orphan*/  uflag; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  bwsfwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closefile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 scalar_t__ list_coll (struct sort_list_item**,struct sort_list_item**) ; 
 int /*<<< orphan*/ * openfile (char const*,char*) ; 
 TYPE_1__ sort_opts_vals ; 

void
sort_list_dump(struct sort_list *l, const char *fn)
{

	if (l && fn) {
		FILE *f;

		f = openfile(fn, "w");
		if (f == NULL)
			err(2, NULL);

		if (l->list) {
			size_t i;
			if (!(sort_opts_vals.uflag)) {
				for (i = 0; i < l->count; ++i)
					bwsfwrite(l->list[i]->str, f,
					    sort_opts_vals.zflag);
			} else {
				struct sort_list_item *last_printed_item = NULL;
				struct sort_list_item *item;
				for (i = 0; i < l->count; ++i) {
					item = l->list[i];
					if ((last_printed_item == NULL) ||
					    list_coll(&last_printed_item, &item)) {
						bwsfwrite(item->str, f, sort_opts_vals.zflag);
						last_printed_item = item;
					}
				}
			}
		}

		closefile(f, fn);
	}
}