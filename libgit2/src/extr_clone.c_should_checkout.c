#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_3__ {scalar_t__ checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 scalar_t__ GIT_CHECKOUT_NONE ; 
 int /*<<< orphan*/  git_repository_head_unborn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool should_checkout(
	git_repository *repo,
	bool is_bare,
	const git_checkout_options *opts)
{
	if (is_bare)
		return false;

	if (!opts)
		return false;

	if (opts->checkout_strategy == GIT_CHECKOUT_NONE)
		return false;

	return !git_repository_head_unborn(repo);
}