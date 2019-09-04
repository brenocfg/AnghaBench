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
typedef  int uint32_t ;
struct shallow_info {int** used_shallow; scalar_t__* shallow_ref; TYPE_1__* shallow; } ;
struct oid_array {int nr; int /*<<< orphan*/ * oid; } ;
struct lock_file {int dummy; } ;
struct command {int index; int /*<<< orphan*/  ref_name; } ;
struct check_connected_options {int /*<<< orphan*/  shallow_file; int /*<<< orphan*/  env; } ;
struct TYPE_2__ {int nr; int /*<<< orphan*/ * oid; } ;

/* Variables and functions */
 struct check_connected_options CHECK_CONNECTED_INIT ; 
 struct lock_file LOCK_INIT ; 
 struct oid_array OID_ARRAY_INIT ; 
 scalar_t__ check_connected (int /*<<< orphan*/ ,struct command*,struct check_connected_options*) ; 
 int /*<<< orphan*/  command_singleton_iterator ; 
 int /*<<< orphan*/  commit_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  delayed_reachability_test (struct shallow_info*,int) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int /*<<< orphan*/  register_shallow (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  setup_alternate_shallow (struct lock_file*,int /*<<< orphan*/ *,struct oid_array*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  tmp_objdir ; 
 int /*<<< orphan*/  tmp_objdir_env (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_shallow ; 

__attribute__((used)) static int update_shallow_ref(struct command *cmd, struct shallow_info *si)
{
	struct lock_file shallow_lock = LOCK_INIT;
	struct oid_array extra = OID_ARRAY_INIT;
	struct check_connected_options opt = CHECK_CONNECTED_INIT;
	uint32_t mask = 1 << (cmd->index % 32);
	int i;

	trace_printf_key(&trace_shallow,
			 "shallow: update_shallow_ref %s\n", cmd->ref_name);
	for (i = 0; i < si->shallow->nr; i++)
		if (si->used_shallow[i] &&
		    (si->used_shallow[i][cmd->index / 32] & mask) &&
		    !delayed_reachability_test(si, i))
			oid_array_append(&extra, &si->shallow->oid[i]);

	opt.env = tmp_objdir_env(tmp_objdir);
	setup_alternate_shallow(&shallow_lock, &opt.shallow_file, &extra);
	if (check_connected(command_singleton_iterator, cmd, &opt)) {
		rollback_lock_file(&shallow_lock);
		oid_array_clear(&extra);
		return -1;
	}

	commit_lock_file(&shallow_lock);

	/*
	 * Make sure setup_alternate_shallow() for the next ref does
	 * not lose these new roots..
	 */
	for (i = 0; i < extra.nr; i++)
		register_shallow(the_repository, &extra.oid[i]);

	si->shallow_ref[cmd->index] = 0;
	oid_array_clear(&extra);
	return 0;
}