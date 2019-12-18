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
struct sort_list_item {int dummy; } ;
struct sort_list {size_t count; size_t size; size_t memsize; int /*<<< orphan*/ * list; } ;
struct bwstring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sort_list_item_alloc () ; 
 int /*<<< orphan*/  sort_list_item_set (int /*<<< orphan*/ ,struct bwstring*) ; 
 scalar_t__ sort_list_item_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sort_realloc (int /*<<< orphan*/ *,int) ; 

void
sort_list_add(struct sort_list *l, struct bwstring *str)
{

	if (l && str) {
		size_t indx = l->count;

		if ((l->list == NULL) || (indx >= l->size)) {
			size_t newsize = (l->size + 1) + 1024;

			l->list = sort_realloc(l->list,
			    sizeof(struct sort_list_item*) * newsize);
			l->memsize += (newsize - l->size) *
			    sizeof(struct sort_list_item*);
			l->size = newsize;
		}
		l->list[indx] = sort_list_item_alloc();
		sort_list_item_set(l->list[indx], str);
		l->memsize += sort_list_item_size(l->list[indx]);
		l->count += 1;
	}
}