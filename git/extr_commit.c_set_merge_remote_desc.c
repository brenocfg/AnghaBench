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
struct object {int dummy; } ;
struct merge_remote_desc {struct object* obj; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct merge_remote_desc*,char const*,char const*) ; 
 int /*<<< orphan*/  merge_desc_slab ; 
 struct merge_remote_desc** merge_desc_slab_at (int /*<<< orphan*/ *,struct commit*) ; 

void set_merge_remote_desc(struct commit *commit,
			   const char *name, struct object *obj)
{
	struct merge_remote_desc *desc;
	FLEX_ALLOC_STR(desc, name, name);
	desc->obj = obj;
	*merge_desc_slab_at(&merge_desc_slab, commit) = desc;
}