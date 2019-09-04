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
struct rename_conflict_info {int dummy; } ;
struct object_id {int dummy; } ;
struct merge_options {int dummy; } ;

/* Variables and functions */
 int handle_content_merge (struct merge_options*,char const*,int /*<<< orphan*/ ,struct object_id*,unsigned int,struct object_id*,unsigned int,struct object_id*,unsigned int,struct rename_conflict_info*) ; 
 int /*<<< orphan*/  was_dirty (struct merge_options*,char const*) ; 

__attribute__((used)) static int handle_rename_normal(struct merge_options *o,
				const char *path,
				struct object_id *o_oid, unsigned int o_mode,
				struct object_id *a_oid, unsigned int a_mode,
				struct object_id *b_oid, unsigned int b_mode,
				struct rename_conflict_info *ci)
{
	/* Merge the content and write it out */
	return handle_content_merge(o, path, was_dirty(o, path),
				    o_oid, o_mode, a_oid, a_mode, b_oid, b_mode,
				    ci);
}