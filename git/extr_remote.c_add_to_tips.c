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
struct tips {scalar_t__ nr; struct commit** tip; int /*<<< orphan*/  alloc; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct commit**,scalar_t__,int /*<<< orphan*/ ) ; 
 int TMP_MARK ; 
 scalar_t__ is_null_oid (struct object_id const*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id const*,int) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void add_to_tips(struct tips *tips, const struct object_id *oid)
{
	struct commit *commit;

	if (is_null_oid(oid))
		return;
	commit = lookup_commit_reference_gently(the_repository, oid, 1);
	if (!commit || (commit->object.flags & TMP_MARK))
		return;
	commit->object.flags |= TMP_MARK;
	ALLOC_GROW(tips->tip, tips->nr + 1, tips->alloc);
	tips->tip[tips->nr++] = commit;
}