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
struct TYPE_2__ {scalar_t__ hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int /*<<< orphan*/  UPDATE_REFS_DIE_ON_ERR ; 
 char** argv_checkout ; 
 char** argv_show_branch ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int run_command_v_opt (char**,int /*<<< orphan*/ ) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  update_ref (int /*<<< orphan*/ *,char*,struct object_id const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bisect_checkout(const struct object_id *bisect_rev, int no_checkout)
{
	char bisect_rev_hex[GIT_MAX_HEXSZ + 1];

	memcpy(bisect_rev_hex, oid_to_hex(bisect_rev), the_hash_algo->hexsz + 1);
	update_ref(NULL, "BISECT_EXPECTED_REV", bisect_rev, NULL, 0, UPDATE_REFS_DIE_ON_ERR);

	argv_checkout[2] = bisect_rev_hex;
	if (no_checkout) {
		update_ref(NULL, "BISECT_HEAD", bisect_rev, NULL, 0,
			   UPDATE_REFS_DIE_ON_ERR);
	} else {
		int res;
		res = run_command_v_opt(argv_checkout, RUN_GIT_CMD);
		if (res)
			exit(res);
	}

	argv_show_branch[1] = bisect_rev_hex;
	return run_command_v_opt(argv_show_branch, RUN_GIT_CMD);
}