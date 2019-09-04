#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {scalar_t__ commit_count; int /*<<< orphan*/ ** commits; } ;
typedef  TYPE_1__ describe_options ;

/* Variables and functions */
 int /*<<< orphan*/  do_describe_single (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_describe(git_repository *repo, describe_options *opts)
{
	if (opts->commit_count == 0)
		do_describe_single(repo, opts, NULL);
	else
	{
		size_t i;
		for (i = 0; i < opts->commit_count; i++)
			do_describe_single(repo, opts, opts->commits[i]);
	}
}