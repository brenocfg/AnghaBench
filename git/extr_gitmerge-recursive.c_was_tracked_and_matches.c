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
struct object_id {int dummy; } ;
struct TYPE_2__ {struct cache_entry** cache; } ;
struct merge_options {TYPE_1__ orig_index; } ;
struct cache_entry {unsigned int ce_mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int index_name_pos (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ oid_eq (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int was_tracked_and_matches(struct merge_options *o, const char *path,
				   const struct object_id *oid, unsigned mode)
{
	int pos = index_name_pos(&o->orig_index, path, strlen(path));
	struct cache_entry *ce;

	if (0 > pos)
		/* we were not tracking this path before the merge */
		return 0;

	/* See if the file we were tracking before matches */
	ce = o->orig_index.cache[pos];
	return (oid_eq(&ce->oid, oid) && ce->ce_mode == mode);
}