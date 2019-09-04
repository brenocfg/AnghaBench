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
struct TYPE_2__ {int close_file; int /*<<< orphan*/  file; } ;
struct rev_info {char* break_bar; TYPE_1__ diffopt; struct log_info* loginfo; scalar_t__ reverse_output_stage; int /*<<< orphan*/  linear; scalar_t__ track_linear; scalar_t__ always_show_header; scalar_t__ line_level_traverse; } ;
struct log_info {int /*<<< orphan*/ * parent; struct commit* commit; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int line_log_print (struct rev_info*,struct commit*) ; 
 int log_tree_diff (struct rev_info*,struct commit*,struct log_info*) ; 
 int /*<<< orphan*/  maybe_flush_or_die (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_log (struct rev_info*) ; 

int log_tree_commit(struct rev_info *opt, struct commit *commit)
{
	struct log_info log;
	int shown, close_file = opt->diffopt.close_file;

	log.commit = commit;
	log.parent = NULL;
	opt->loginfo = &log;
	opt->diffopt.close_file = 0;

	if (opt->line_level_traverse)
		return line_log_print(opt, commit);

	if (opt->track_linear && !opt->linear && !opt->reverse_output_stage)
		fprintf(opt->diffopt.file, "\n%s\n", opt->break_bar);
	shown = log_tree_diff(opt, commit, &log);
	if (!shown && opt->loginfo && opt->always_show_header) {
		log.parent = NULL;
		show_log(opt);
		shown = 1;
	}
	if (opt->track_linear && !opt->linear && opt->reverse_output_stage)
		fprintf(opt->diffopt.file, "\n%s\n", opt->break_bar);
	opt->loginfo = NULL;
	maybe_flush_or_die(opt->diffopt.file, "stdout");
	if (close_file)
		fclose(opt->diffopt.file);
	return shown;
}