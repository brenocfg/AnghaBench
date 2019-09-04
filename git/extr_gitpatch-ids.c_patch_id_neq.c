#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct patch_id {int /*<<< orphan*/  patch_id; TYPE_2__* commit; } ;
struct diff_options {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ commit_patch_id (TYPE_2__*,struct diff_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int patch_id_neq(const void *cmpfn_data,
			const void *entry,
			const void *entry_or_key,
			const void *unused_keydata)
{
	/* NEEDSWORK: const correctness? */
	struct diff_options *opt = (void *)cmpfn_data;
	struct patch_id *a = (void *)entry;
	struct patch_id *b = (void *)entry_or_key;

	if (is_null_oid(&a->patch_id) &&
	    commit_patch_id(a->commit, opt, &a->patch_id, 0))
		return error("Could not get patch ID for %s",
			oid_to_hex(&a->commit->object.oid));
	if (is_null_oid(&b->patch_id) &&
	    commit_patch_id(b->commit, opt, &b->patch_id, 0))
		return error("Could not get patch ID for %s",
			oid_to_hex(&b->commit->object.oid));
	return !oideq(&a->patch_id, &b->patch_id);
}