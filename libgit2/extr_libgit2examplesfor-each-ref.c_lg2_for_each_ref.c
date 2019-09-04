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

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (char**) ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_ref ; 

int lg2_for_each_ref(git_repository *repo, int argc, char **argv)
{
	UNUSED(argv);

        if (argc != 1)
                fatal("Sorry, no for-each-ref options supported yet", NULL);

        check_lg2(git_reference_foreach(repo, show_ref, repo),
                  "Could not iterate over references", NULL);

        return 0;
}