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
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;
typedef  enum commit_msg_cleanup_mode { ____Placeholder_commit_msg_cleanup_mode } commit_msg_cleanup_mode ;

/* Variables and functions */
 int COMMIT_MSG_CLEANUP_SCISSORS ; 
 scalar_t__ ce_stage (struct cache_entry const*) ; 
 char comment_line_char ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_commented_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wt_status_append_cut_line (struct strbuf*) ; 

void append_conflicts_hint(struct index_state *istate,
	struct strbuf *msgbuf, enum commit_msg_cleanup_mode cleanup_mode)
{
	int i;

	if (cleanup_mode == COMMIT_MSG_CLEANUP_SCISSORS) {
		strbuf_addch(msgbuf, '\n');
		wt_status_append_cut_line(msgbuf);
		strbuf_addch(msgbuf, comment_line_char);
	}

	strbuf_addch(msgbuf, '\n');
	strbuf_commented_addf(msgbuf, "Conflicts:\n");
	for (i = 0; i < istate->cache_nr;) {
		const struct cache_entry *ce = istate->cache[i++];
		if (ce_stage(ce)) {
			strbuf_commented_addf(msgbuf, "\t%s\n", ce->name);
			while (i < istate->cache_nr &&
			       !strcmp(ce->name, istate->cache[i]->name))
				i++;
		}
	}
}