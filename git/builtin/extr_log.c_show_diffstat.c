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
struct TYPE_2__ {int /*<<< orphan*/  file; } ;
struct rev_info {TYPE_1__ diffopt; } ;
struct diff_options {int output_format; } ;
struct commit {int dummy; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int DIFF_FORMAT_DIFFSTAT ; 
 int DIFF_FORMAT_SUMMARY ; 
 int /*<<< orphan*/  diff_flush (struct diff_options*) ; 
 int /*<<< orphan*/  diff_setup_done (struct diff_options*) ; 
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_std (struct diff_options*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_commit_tree_oid (struct commit*) ; 
 int /*<<< orphan*/  memcpy (struct diff_options*,TYPE_1__*,int) ; 

__attribute__((used)) static void show_diffstat(struct rev_info *rev,
			  struct commit *origin, struct commit *head)
{
	struct diff_options opts;

	memcpy(&opts, &rev->diffopt, sizeof(opts));
	opts.output_format = DIFF_FORMAT_SUMMARY | DIFF_FORMAT_DIFFSTAT;
	diff_setup_done(&opts);

	diff_tree_oid(get_commit_tree_oid(origin),
		      get_commit_tree_oid(head),
		      "", &opts);
	diffcore_std(&opts);
	diff_flush(&opts);

	fprintf(rev->diffopt.file, "\n");
}