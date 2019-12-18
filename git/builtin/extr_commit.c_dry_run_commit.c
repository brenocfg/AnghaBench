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
struct wt_status {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 char* prepare_index (int,char const**,char const*,struct commit const*,int) ; 
 int /*<<< orphan*/  rollback_index_files () ; 
 int run_status (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int dry_run_commit(int argc, const char **argv, const char *prefix,
			  const struct commit *current_head, struct wt_status *s)
{
	int committable;
	const char *index_file;

	index_file = prepare_index(argc, argv, prefix, current_head, 1);
	committable = run_status(stdout, index_file, prefix, 0, s);
	rollback_index_files();

	return committable ? 0 : 1;
}