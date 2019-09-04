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
struct rev_info {int /*<<< orphan*/  diffopt; } ;
struct object_id {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_addremove (int /*<<< orphan*/ *,char const,unsigned int,struct object_id const*,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void diff_index_show_file(struct rev_info *revs,
				 const char *prefix,
				 const struct cache_entry *ce,
				 const struct object_id *oid, int oid_valid,
				 unsigned int mode,
				 unsigned dirty_submodule)
{
	diff_addremove(&revs->diffopt, prefix[0], mode,
		       oid, oid_valid, ce->name, dirty_submodule);
}