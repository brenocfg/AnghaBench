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
struct option {struct diff_options* value; } ;
struct diff_options {scalar_t__ anchors_nr; int /*<<< orphan*/ * anchors; int /*<<< orphan*/  anchors_alloc; int /*<<< orphan*/  xdl_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  DIFF_WITH_ALG (struct diff_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATIENCE_DIFF ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int diff_opt_anchored(const struct option *opt,
			     const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->xdl_opts = DIFF_WITH_ALG(options, PATIENCE_DIFF);
	ALLOC_GROW(options->anchors, options->anchors_nr + 1,
		   options->anchors_alloc);
	options->anchors[options->anchors_nr++] = xstrdup(arg);
	return 0;
}