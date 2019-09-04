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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_FORCE_CREATE_REFLOG ; 
 int /*<<< orphan*/  UPDATE_REFS_MSG_ON_ERR ; 
 int /*<<< orphan*/  UPDATE_REFS_QUIET_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  ref_stash ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ update_ref (char const*,int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_store_stash(const struct object_id *w_commit, const char *stash_msg,
			  int quiet)
{
	if (!stash_msg)
		stash_msg = "Created via \"git stash store\".";

	if (update_ref(stash_msg, ref_stash, w_commit, NULL,
		       REF_FORCE_CREATE_REFLOG,
		       quiet ? UPDATE_REFS_QUIET_ON_ERR :
		       UPDATE_REFS_MSG_ON_ERR)) {
		if (!quiet) {
			fprintf_ln(stderr, _("Cannot update %s with %s"),
				   ref_stash, oid_to_hex(w_commit));
		}
		return -1;
	}

	return 0;
}