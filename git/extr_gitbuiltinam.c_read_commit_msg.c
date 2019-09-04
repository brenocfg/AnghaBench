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
struct am_state {int /*<<< orphan*/  msg_len; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ read_state_file (struct strbuf*,struct am_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int read_commit_msg(struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;

	assert(!state->msg);

	if (read_state_file(&sb, state, "final-commit", 0) < 0) {
		strbuf_release(&sb);
		return -1;
	}

	state->msg = strbuf_detach(&sb, &state->msg_len);
	return 0;
}