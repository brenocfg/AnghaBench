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
struct traverse_info {int dummy; } ;
struct name_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;
struct merge_list {struct merge_list* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_merge_entry (struct merge_list*) ; 
 struct merge_list* create_entry (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 char* traverse_path (struct traverse_info const*,struct name_entry*) ; 

__attribute__((used)) static void resolve(const struct traverse_info *info, struct name_entry *ours, struct name_entry *result)
{
	struct merge_list *orig, *final;
	const char *path;

	/* If it's already ours, don't bother showing it */
	if (!ours)
		return;

	path = traverse_path(info, result);
	orig = create_entry(2, ours->mode, &ours->oid, path);
	final = create_entry(0, result->mode, &result->oid, path);

	final->link = orig;

	add_merge_entry(final);
}