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
struct oid_array {int nr; int /*<<< orphan*/ * oid; } ;
struct object_id {int dummy; } ;
struct diff_options {int output_format; char* orderfile; } ;
struct combine_diff_path {int dummy; } ;

/* Variables and functions */
 void* DIFF_FORMAT_NO_OUTPUT ; 
 int STAT_FORMAT_MASK ; 
 int /*<<< orphan*/  diff_flush (struct diff_options*) ; 
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ *,struct object_id const*,char*,struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_order (char const*) ; 
 int /*<<< orphan*/  diffcore_std (struct diff_options*) ; 
 struct combine_diff_path* intersect_paths (struct combine_diff_path*,int,int,int) ; 

__attribute__((used)) static struct combine_diff_path *find_paths_generic(const struct object_id *oid,
	const struct oid_array *parents,
	struct diff_options *opt,
	int combined_all_paths)
{
	struct combine_diff_path *paths = NULL;
	int i, num_parent = parents->nr;

	int output_format = opt->output_format;
	const char *orderfile = opt->orderfile;

	opt->output_format = DIFF_FORMAT_NO_OUTPUT;
	/* tell diff_tree to emit paths in sorted (=tree) order */
	opt->orderfile = NULL;

	/* D(A,P1...Pn) = D(A,P1) ^ ... ^ D(A,Pn)  (wrt paths) */
	for (i = 0; i < num_parent; i++) {
		/*
		 * show stat against the first parent even when doing
		 * combined diff.
		 */
		int stat_opt = output_format & STAT_FORMAT_MASK;
		if (i == 0 && stat_opt)
			opt->output_format = stat_opt;
		else
			opt->output_format = DIFF_FORMAT_NO_OUTPUT;
		diff_tree_oid(&parents->oid[i], oid, "", opt);
		diffcore_std(opt);
		paths = intersect_paths(paths, i, num_parent,
					combined_all_paths);

		/* if showing diff, show it in requested order */
		if (opt->output_format != DIFF_FORMAT_NO_OUTPUT &&
		    orderfile) {
			diffcore_order(orderfile);
		}

		diff_flush(opt);
	}

	opt->output_format = output_format;
	opt->orderfile = orderfile;
	return paths;
}