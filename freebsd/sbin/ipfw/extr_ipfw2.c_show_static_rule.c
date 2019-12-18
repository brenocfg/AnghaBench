#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct show_state {int flags; } ;
struct ip_fw_rule {int set; int flags; int /*<<< orphan*/  rulenum; } ;
struct ip_fw_bcounter {scalar_t__ timestamp; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; } ;
struct format_opts {int set_mask; scalar_t__ pcwidth; scalar_t__ bcwidth; } ;
struct cmdline_opts {scalar_t__ do_time; scalar_t__ comment_only; scalar_t__ do_compact; scalar_t__ show_sets; } ;
struct buf_pr {int dummy; } ;
struct TYPE_4__ {int opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 int HAVE_DSTIP ; 
 int HAVE_PROTO ; 
 int HAVE_SRCIP ; 
 int IPFW_RULE_JUSTOPTS ; 
 int IPFW_RULE_NOOPT ; 
#define  O_CHECK_STATE 130 
#define  O_EXTERNAL_ACTION 129 
#define  O_EXTERNAL_INSTANCE 128 
 int /*<<< orphan*/  O_IP_DSTPORT ; 
 int /*<<< orphan*/  O_IP_SRCPORT ; 
 int O_NOP ; 
 int O_PROB ; 
 scalar_t__ TIMESTAMP_NUMERIC ; 
 scalar_t__ TIMESTAMP_STRING ; 
 int /*<<< orphan*/  _long_to_time (scalar_t__) ; 
 int /*<<< orphan*/ * action_opcodes ; 
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,...) ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dst_opcodes ; 
 int /*<<< orphan*/  free_show_state (struct show_state*) ; 
 scalar_t__ init_show_state (struct show_state*,struct ip_fw_rule*) ; 
 int /*<<< orphan*/ * modifier_opcodes ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_u64 (struct buf_pr*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* print_action (struct buf_pr*,struct format_opts*,struct show_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_address (struct buf_pr*,struct format_opts*,struct show_state*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* print_opcode (struct buf_pr*,struct format_opts*,struct show_state*,int) ; 
 int /*<<< orphan*/  print_proto (struct buf_pr*,struct format_opts*,struct show_state*) ; 
 int /*<<< orphan*/ * src_opcodes ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
show_static_rule(struct cmdline_opts *co, struct format_opts *fo,
    struct buf_pr *bp, struct ip_fw_rule *rule, struct ip_fw_bcounter *cntr)
{
	struct show_state state;
	ipfw_insn *cmd;
	static int twidth = 0;
	int i;

	/* Print # DISABLED or skip the rule */
	if ((fo->set_mask & (1 << rule->set)) == 0) {
		/* disabled mask */
		if (!co->show_sets)
			return;
		else
			bprintf(bp, "# DISABLED ");
	}
	if (init_show_state(&state, rule) != 0) {
		warn("init_show_state() failed");
		return;
	}
	bprintf(bp, "%05u ", rule->rulenum);

	/* Print counters if enabled */
	if (fo->pcwidth > 0 || fo->bcwidth > 0) {
		pr_u64(bp, &cntr->pcnt, fo->pcwidth);
		pr_u64(bp, &cntr->bcnt, fo->bcwidth);
	}

	/* Print timestamp */
	if (co->do_time == TIMESTAMP_NUMERIC)
		bprintf(bp, "%10u ", cntr->timestamp);
	else if (co->do_time == TIMESTAMP_STRING) {
		char timestr[30];
		time_t t = (time_t)0;

		if (twidth == 0) {
			strcpy(timestr, ctime(&t));
			*strchr(timestr, '\n') = '\0';
			twidth = strlen(timestr);
		}
		if (cntr->timestamp > 0) {
			t = _long_to_time(cntr->timestamp);

			strcpy(timestr, ctime(&t));
			*strchr(timestr, '\n') = '\0';
			bprintf(bp, "%s ", timestr);
		} else {
			bprintf(bp, "%*s", twidth, " ");
		}
	}

	/* Print set number */
	if (co->show_sets)
		bprintf(bp, "set %d ", rule->set);

	/* Print the optional "match probability" */
	cmd = print_opcode(bp, fo, &state, O_PROB);
	/* Print rule action */
	for (i = 0; i < nitems(action_opcodes); i++) {
		cmd = print_action(bp, fo, &state, action_opcodes[i]);
		if (cmd == NULL)
			continue;
		/* Handle special cases */
		switch (cmd->opcode) {
		case O_CHECK_STATE:
			goto end;
		case O_EXTERNAL_ACTION:
		case O_EXTERNAL_INSTANCE:
			/* External action can have several instructions */
			continue;
		}
		break;
	}
	/* Print rule modifiers */
	for (i = 0; i < nitems(modifier_opcodes); i++)
		print_action(bp, fo, &state, modifier_opcodes[i]);
	/*
	 * Print rule body
	 */
	if (co->comment_only != 0)
		goto end;

	if (rule->flags & IPFW_RULE_JUSTOPTS) {
		state.flags |= HAVE_PROTO | HAVE_SRCIP | HAVE_DSTIP;
		goto justopts;
	}

	print_proto(bp, fo, &state);
	if (co->do_compact != 0 && (rule->flags & IPFW_RULE_NOOPT))
		goto justopts;

	/* Print source */
	bprintf(bp, " from");
	print_address(bp, fo, &state, src_opcodes, nitems(src_opcodes),
	    O_IP_SRCPORT, HAVE_SRCIP);

	/* Print destination */
	bprintf(bp, " to");
	print_address(bp, fo, &state, dst_opcodes, nitems(dst_opcodes),
	    O_IP_DSTPORT, HAVE_DSTIP);

justopts:
	/* Print the rest of options */
	while (print_opcode(bp, fo, &state, -1))
		;
end:
	/* Print comment at the end */
	cmd = print_opcode(bp, fo, &state, O_NOP);
	if (co->comment_only != 0 && cmd == NULL)
		bprintf(bp, " // ...");
	bprintf(bp, "\n");
	free_show_state(&state);
}