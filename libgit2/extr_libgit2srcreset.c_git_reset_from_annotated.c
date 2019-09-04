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
typedef  int /*<<< orphan*/  git_reset_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_checkout_options ;
struct TYPE_3__ {int /*<<< orphan*/  description; scalar_t__ commit; } ;
typedef  TYPE_1__ git_annotated_commit ;

/* Variables and functions */
 int reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int git_reset_from_annotated(
	git_repository *repo,
	const git_annotated_commit *commit,
	git_reset_t reset_type,
	const git_checkout_options *checkout_opts)
{
	return reset(repo, (git_object *) commit->commit, commit->description, reset_type, checkout_opts);
}