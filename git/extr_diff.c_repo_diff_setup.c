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
struct repository {int dummy; } ;
struct TYPE_2__ {int rename_empty; } ;
struct diff_options {char* output_indicators; char line_termination; int break_opt; int rename_limit; char* a_prefix; char* b_prefix; int /*<<< orphan*/  color_moved_ws_handling; int /*<<< orphan*/  color_moved; int /*<<< orphan*/  orderfile; int /*<<< orphan*/  xdl_opts; int /*<<< orphan*/  detect_rename; int /*<<< orphan*/  use_color; int /*<<< orphan*/  add_remove; int /*<<< orphan*/  change; int /*<<< orphan*/ * objfind; TYPE_1__ flags; int /*<<< orphan*/  ws_error_highlight; int /*<<< orphan*/  interhunkcontext; int /*<<< orphan*/  context; int /*<<< orphan*/  dirstat_permille; int /*<<< orphan*/  abbrev; struct repository* repo; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  DIFF_XDL_SET (struct diff_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDENT_HEURISTIC ; 
 size_t OUTPUT_INDICATOR_CONTEXT ; 
 size_t OUTPUT_INDICATOR_NEW ; 
 size_t OUTPUT_INDICATOR_OLD ; 
 int /*<<< orphan*/  default_diff_options ; 
 int /*<<< orphan*/  diff_addremove ; 
 int /*<<< orphan*/  diff_algorithm ; 
 int /*<<< orphan*/  diff_change ; 
 int /*<<< orphan*/  diff_color_moved_default ; 
 int /*<<< orphan*/  diff_color_moved_ws_default ; 
 int /*<<< orphan*/  diff_context_default ; 
 int /*<<< orphan*/  diff_detect_rename_default ; 
 int /*<<< orphan*/  diff_dirstat_permille_default ; 
 scalar_t__ diff_indent_heuristic ; 
 int /*<<< orphan*/  diff_interhunk_context_default ; 
 int /*<<< orphan*/  diff_mnemonic_prefix ; 
 scalar_t__ diff_no_prefix ; 
 int /*<<< orphan*/  diff_order_file_cfg ; 
 int /*<<< orphan*/  diff_use_color_default ; 
 int /*<<< orphan*/  memcpy (struct diff_options*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prep_parse_options (struct diff_options*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  ws_error_highlight_default ; 

void repo_diff_setup(struct repository *r, struct diff_options *options)
{
	memcpy(options, &default_diff_options, sizeof(*options));

	options->file = stdout;
	options->repo = r;

	options->output_indicators[OUTPUT_INDICATOR_NEW] = '+';
	options->output_indicators[OUTPUT_INDICATOR_OLD] = '-';
	options->output_indicators[OUTPUT_INDICATOR_CONTEXT] = ' ';
	options->abbrev = DEFAULT_ABBREV;
	options->line_termination = '\n';
	options->break_opt = -1;
	options->rename_limit = -1;
	options->dirstat_permille = diff_dirstat_permille_default;
	options->context = diff_context_default;
	options->interhunkcontext = diff_interhunk_context_default;
	options->ws_error_highlight = ws_error_highlight_default;
	options->flags.rename_empty = 1;
	options->objfind = NULL;

	/* pathchange left =NULL by default */
	options->change = diff_change;
	options->add_remove = diff_addremove;
	options->use_color = diff_use_color_default;
	options->detect_rename = diff_detect_rename_default;
	options->xdl_opts |= diff_algorithm;
	if (diff_indent_heuristic)
		DIFF_XDL_SET(options, INDENT_HEURISTIC);

	options->orderfile = diff_order_file_cfg;

	if (diff_no_prefix) {
		options->a_prefix = options->b_prefix = "";
	} else if (!diff_mnemonic_prefix) {
		options->a_prefix = "a/";
		options->b_prefix = "b/";
	}

	options->color_moved = diff_color_moved_default;
	options->color_moved_ws_handling = diff_color_moved_ws_default;

	prep_parse_options(options);
}