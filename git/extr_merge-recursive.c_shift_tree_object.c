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
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct tree* lookup_tree (struct repository*,struct object_id*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  shift_tree (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shift_tree_by (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct object_id*,char const*) ; 

__attribute__((used)) static struct tree *shift_tree_object(struct repository *repo,
				      struct tree *one, struct tree *two,
				      const char *subtree_shift)
{
	struct object_id shifted;

	if (!*subtree_shift) {
		shift_tree(repo, &one->object.oid, &two->object.oid, &shifted, 0);
	} else {
		shift_tree_by(repo, &one->object.oid, &two->object.oid, &shifted,
			      subtree_shift);
	}
	if (oideq(&two->object.oid, &shifted))
		return two;
	return lookup_tree(repo, &shifted);
}