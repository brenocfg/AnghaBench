#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct opts {int output; } ;
typedef  int /*<<< orphan*/  git_diff_stats_format_t ;
typedef  int /*<<< orphan*/  git_diff_stats ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT_CONST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_DIFF_STATS_FULL ; 
 int /*<<< orphan*/  GIT_DIFF_STATS_INCLUDE_SUMMARY ; 
 int /*<<< orphan*/  GIT_DIFF_STATS_NUMBER ; 
 int /*<<< orphan*/  GIT_DIFF_STATS_SHORT ; 
 int OUTPUT_NUMSTAT ; 
 int OUTPUT_SHORTSTAT ; 
 int OUTPUT_STAT ; 
 int OUTPUT_SUMMARY ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_get_stats (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_stats_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_stats_to_buf (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void diff_print_stats(git_diff *diff, struct opts *o)
{
	git_diff_stats *stats;
	git_buf b = GIT_BUF_INIT_CONST(NULL, 0);
	git_diff_stats_format_t format = 0;

	check_lg2(
		git_diff_get_stats(&stats, diff), "generating stats for diff", NULL);

	if (o->output & OUTPUT_STAT)
		format |= GIT_DIFF_STATS_FULL;
	if (o->output & OUTPUT_SHORTSTAT)
		format |= GIT_DIFF_STATS_SHORT;
	if (o->output & OUTPUT_NUMSTAT)
		format |= GIT_DIFF_STATS_NUMBER;
	if (o->output & OUTPUT_SUMMARY)
		format |= GIT_DIFF_STATS_INCLUDE_SUMMARY;

	check_lg2(
		git_diff_stats_to_buf(&b, stats, format, 80), "formatting stats", NULL);

	fputs(b.ptr, stdout);

	git_buf_dispose(&b);
	git_diff_stats_free(stats);
}