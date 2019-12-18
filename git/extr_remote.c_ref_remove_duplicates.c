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
struct string_list_item {struct ref* util; } ;
struct string_list {int dummy; } ;
struct ref {struct ref* next; TYPE_1__* peer_ref; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  handle_duplicate (struct ref*,struct ref*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 struct string_list_item* string_list_insert (struct string_list*,int /*<<< orphan*/ ) ; 

struct ref *ref_remove_duplicates(struct ref *ref_map)
{
	struct string_list refs = STRING_LIST_INIT_NODUP;
	struct ref *retval = NULL;
	struct ref **p = &retval;

	while (ref_map) {
		struct ref *ref = ref_map;

		ref_map = ref_map->next;
		ref->next = NULL;

		if (!ref->peer_ref) {
			*p = ref;
			p = &ref->next;
		} else {
			struct string_list_item *item =
				string_list_insert(&refs, ref->peer_ref->name);

			if (item->util) {
				/* Entry already existed */
				handle_duplicate((struct ref *)item->util, ref);
			} else {
				*p = ref;
				p = &ref->next;
				item->util = ref;
			}
		}
	}

	string_list_clear(&refs, 0);
	return retval;
}