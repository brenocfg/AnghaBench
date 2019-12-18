#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  exit_with_status; } ;
struct TYPE_5__ {TYPE_1__ flags; } ;
struct rev_info {struct log_info* loginfo; TYPE_2__ diffopt; scalar_t__ first_parent_only; scalar_t__ combine_merges; scalar_t__ ignore_merges; scalar_t__ show_root_diff; int /*<<< orphan*/  diff; } ;
struct object_id {int dummy; } ;
struct log_info {struct commit* parent; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_root_tree_oid (struct object_id*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  diff_tree_oid (struct object_id*,struct object_id*,char*,TYPE_2__*) ; 
 int do_diff_combined (struct rev_info*,struct commit*) ; 
 struct object_id* get_commit_tree_oid (struct commit*) ; 
 struct commit_list* get_saved_parents (struct rev_info*,struct commit*) ; 
 int /*<<< orphan*/  log_tree_diff_flush (struct rev_info*) ; 
 int /*<<< orphan*/  parse_commit_or_die (struct commit*) ; 

__attribute__((used)) static int log_tree_diff(struct rev_info *opt, struct commit *commit, struct log_info *log)
{
	int showed_log;
	struct commit_list *parents;
	struct object_id *oid;

	if (!opt->diff && !opt->diffopt.flags.exit_with_status)
		return 0;

	parse_commit_or_die(commit);
	oid = get_commit_tree_oid(commit);

	/* Root commit? */
	parents = get_saved_parents(opt, commit);
	if (!parents) {
		if (opt->show_root_diff) {
			diff_root_tree_oid(oid, "", &opt->diffopt);
			log_tree_diff_flush(opt);
		}
		return !opt->loginfo;
	}

	/* More than one parent? */
	if (parents && parents->next) {
		if (opt->ignore_merges)
			return 0;
		else if (opt->combine_merges)
			return do_diff_combined(opt, commit);
		else if (opt->first_parent_only) {
			/*
			 * Generate merge log entry only for the first
			 * parent, showing summary diff of the others
			 * we merged _in_.
			 */
			parse_commit_or_die(parents->item);
			diff_tree_oid(get_commit_tree_oid(parents->item),
				      oid, "", &opt->diffopt);
			log_tree_diff_flush(opt);
			return !opt->loginfo;
		}

		/* If we show individual diffs, show the parent info */
		log->parent = parents->item;
	}

	showed_log = 0;
	for (;;) {
		struct commit *parent = parents->item;

		parse_commit_or_die(parent);
		diff_tree_oid(get_commit_tree_oid(parent),
			      oid, "", &opt->diffopt);
		log_tree_diff_flush(opt);

		showed_log |= !opt->loginfo;

		/* Set up the log info for the next parent, if any.. */
		parents = parents->next;
		if (!parents)
			break;
		log->parent = parents->item;
		opt->loginfo = log;
	}
	return showed_log;
}