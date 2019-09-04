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
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REFRESH_QUIET ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ is_null_oid (struct object_id const*) ; 
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  refresh_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_hard (struct object_id const*,int) ; 
 int /*<<< orphan*/  run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void restore_state(const struct object_id *head,
			  const struct object_id *stash)
{
	struct strbuf sb = STRBUF_INIT;
	const char *args[] = { "stash", "apply", NULL, NULL };

	if (is_null_oid(stash))
		return;

	reset_hard(head, 1);

	args[2] = oid_to_hex(stash);

	/*
	 * It is OK to ignore error here, for example when there was
	 * nothing to restore.
	 */
	run_command_v_opt(args, RUN_GIT_CMD);

	strbuf_release(&sb);
	refresh_cache(REFRESH_QUIET);
}