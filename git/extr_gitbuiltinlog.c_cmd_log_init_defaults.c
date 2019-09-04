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
struct TYPE_3__ {int default_follow_renames; int recursive; int allow_textconv; } ;
struct TYPE_4__ {int stat_width; int stat_graph_width; TYPE_1__ flags; } ;
struct rev_info {int verbose_header; int /*<<< orphan*/  date_mode; TYPE_2__ diffopt; int /*<<< orphan*/  show_signature; int /*<<< orphan*/  subject_prefix; int /*<<< orphan*/  show_root_diff; int /*<<< orphan*/  abbrev_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_abbrev_commit ; 
 scalar_t__ default_date_mode ; 
 scalar_t__ default_follow ; 
 int /*<<< orphan*/  default_show_root ; 
 int /*<<< orphan*/  default_show_signature ; 
 int /*<<< orphan*/  fmt_patch_subject_prefix ; 
 scalar_t__ fmt_pretty ; 
 int /*<<< orphan*/  get_commit_format (scalar_t__,struct rev_info*) ; 
 int /*<<< orphan*/  parse_date_format (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmd_log_init_defaults(struct rev_info *rev)
{
	if (fmt_pretty)
		get_commit_format(fmt_pretty, rev);
	if (default_follow)
		rev->diffopt.flags.default_follow_renames = 1;
	rev->verbose_header = 1;
	rev->diffopt.flags.recursive = 1;
	rev->diffopt.stat_width = -1; /* use full terminal width */
	rev->diffopt.stat_graph_width = -1; /* respect statGraphWidth config */
	rev->abbrev_commit = default_abbrev_commit;
	rev->show_root_diff = default_show_root;
	rev->subject_prefix = fmt_patch_subject_prefix;
	rev->show_signature = default_show_signature;
	rev->diffopt.flags.allow_textconv = 1;

	if (default_date_mode)
		parse_date_format(default_date_mode, &rev->date_mode);
}