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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  describe_options ;

/* Variables and functions */
 int /*<<< orphan*/  describe_options_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_describe (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_options (int /*<<< orphan*/ *,int,char**) ; 

int lg2_describe(git_repository *repo, int argc, char **argv)
{
	describe_options opts;

	describe_options_init(&opts);
	parse_options(&opts, argc, argv);

	do_describe(repo, &opts);

	return 0;
}