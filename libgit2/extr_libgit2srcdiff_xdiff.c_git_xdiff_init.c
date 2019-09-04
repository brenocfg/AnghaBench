#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  outf; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int ctxlen; int /*<<< orphan*/  interhunkctxlen; } ;
struct TYPE_9__ {int /*<<< orphan*/  diff_cb; } ;
struct TYPE_13__ {TYPE_4__ callback; TYPE_3__ params; TYPE_2__ config; TYPE_1__ output; } ;
typedef  TYPE_5__ git_xdiff_output ;
struct TYPE_14__ {int flags; int context_lines; int /*<<< orphan*/  interhunk_lines; } ;
typedef  TYPE_6__ git_diff_options ;

/* Variables and functions */
 int GIT_DIFF_IGNORE_WHITESPACE ; 
 int GIT_DIFF_IGNORE_WHITESPACE_CHANGE ; 
 int GIT_DIFF_IGNORE_WHITESPACE_EOL ; 
 int GIT_DIFF_INDENT_HEURISTIC ; 
 int GIT_DIFF_MINIMAL ; 
 int GIT_DIFF_PATIENCE ; 
 int /*<<< orphan*/  XDF_IGNORE_WHITESPACE_AT_EOL ; 
 int /*<<< orphan*/  XDF_IGNORE_WHITESPACE_CHANGE ; 
 int /*<<< orphan*/  XDF_INDENT_HEURISTIC ; 
 int /*<<< orphan*/  XDF_NEED_MINIMAL ; 
 int /*<<< orphan*/  XDF_PATIENCE_DIFF ; 
 int /*<<< orphan*/  XDF_WHITESPACE_FLAGS ; 
 int /*<<< orphan*/  git_xdiff ; 
 int /*<<< orphan*/  git_xdiff_cb ; 

void git_xdiff_init(git_xdiff_output *xo, const git_diff_options *opts)
{
	uint32_t flags = opts ? opts->flags : 0;

	xo->output.diff_cb = git_xdiff;

	xo->config.ctxlen = opts ? opts->context_lines : 3;
	xo->config.interhunkctxlen = opts ? opts->interhunk_lines : 0;

	if (flags & GIT_DIFF_IGNORE_WHITESPACE)
		xo->params.flags |= XDF_WHITESPACE_FLAGS;
	if (flags & GIT_DIFF_IGNORE_WHITESPACE_CHANGE)
		xo->params.flags |= XDF_IGNORE_WHITESPACE_CHANGE;
	if (flags & GIT_DIFF_IGNORE_WHITESPACE_EOL)
		xo->params.flags |= XDF_IGNORE_WHITESPACE_AT_EOL;
	if (flags & GIT_DIFF_INDENT_HEURISTIC)
		xo->params.flags |= XDF_INDENT_HEURISTIC;

	if (flags & GIT_DIFF_PATIENCE)
		xo->params.flags |= XDF_PATIENCE_DIFF;
	if (flags & GIT_DIFF_MINIMAL)
		xo->params.flags |= XDF_NEED_MINIMAL;

	xo->callback.outf = git_xdiff_cb;
}