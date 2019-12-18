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
struct am_state {int /*<<< orphan*/  cur; int /*<<< orphan*/  orig_commit; scalar_t__ msg_len; int /*<<< orphan*/  msg; int /*<<< orphan*/  author_date; int /*<<< orphan*/  author_email; int /*<<< orphan*/  author_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int /*<<< orphan*/  am_path (struct am_state*,char*) ; 
 int /*<<< orphan*/  delete_ref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_oid (char*,struct object_id*) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_state_count (struct am_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_state_text (struct am_state*,char*,char*) ; 

__attribute__((used)) static void am_next(struct am_state *state)
{
	struct object_id head;

	FREE_AND_NULL(state->author_name);
	FREE_AND_NULL(state->author_email);
	FREE_AND_NULL(state->author_date);
	FREE_AND_NULL(state->msg);
	state->msg_len = 0;

	unlink(am_path(state, "author-script"));
	unlink(am_path(state, "final-commit"));

	oidclr(&state->orig_commit);
	unlink(am_path(state, "original-commit"));
	delete_ref(NULL, "REBASE_HEAD", NULL, REF_NO_DEREF);

	if (!get_oid("HEAD", &head))
		write_state_text(state, "abort-safety", oid_to_hex(&head));
	else
		write_state_text(state, "abort-safety", "");

	state->cur++;
	write_state_count(state, "next", state->cur);
}