#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct entry {scalar_t__ ttl; int original_ttl; struct commit* commit; } ;
struct TYPE_5__ {int nr; TYPE_1__* array; } ;
struct data {TYPE_2__ rev_list; } ;
struct TYPE_6__ {int flags; } ;
struct commit {TYPE_3__ object; } ;
struct TYPE_4__ {struct entry* data; } ;

/* Variables and functions */
 int ADVERTISED ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int COMMON ; 
 int POPPED ; 
 int SEEN ; 
 int /*<<< orphan*/  mark_common (struct data*,struct commit*) ; 
 struct entry* rev_list_push (struct data*,struct commit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_parent(struct data *data, struct entry *entry,
		       struct commit *to_push)
{
	struct entry *parent_entry;

	if (to_push->object.flags & SEEN) {
		int i;
		if (to_push->object.flags & POPPED)
			/*
			 * The entry for this commit has already been popped,
			 * due to clock skew. Pretend that this parent does not
			 * exist.
			 */
			return 0;
		/*
		 * Find the existing entry and use it.
		 */
		for (i = 0; i < data->rev_list.nr; i++) {
			parent_entry = data->rev_list.array[i].data;
			if (parent_entry->commit == to_push)
				goto parent_found;
		}
		BUG("missing parent in priority queue");
parent_found:
		;
	} else {
		parent_entry = rev_list_push(data, to_push, 0);
	}

	if (entry->commit->object.flags & (COMMON | ADVERTISED)) {
		mark_common(data, to_push);
	} else {
		uint16_t new_original_ttl = entry->ttl
			? entry->original_ttl : entry->original_ttl * 3 / 2 + 1;
		uint16_t new_ttl = entry->ttl
			? entry->ttl - 1 : new_original_ttl;
		if (parent_entry->original_ttl < new_original_ttl) {
			parent_entry->original_ttl = new_original_ttl;
			parent_entry->ttl = new_ttl;
		}
	}

	return 1;
}