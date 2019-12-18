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
struct parse_state {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_opts (struct parse_state*,int,char**) ; 
 int /*<<< orphan*/  parse_revision (int /*<<< orphan*/ *,struct parse_state*) ; 

int lg2_rev_parse(git_repository *repo, int argc, char *argv[])
{
	struct parse_state ps = {0};

	parse_opts(&ps, argc, argv);

	check_lg2(parse_revision(repo, &ps), "Parsing", NULL);

	return 0;
}