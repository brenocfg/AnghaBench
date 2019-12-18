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
typedef  int /*<<< orphan*/  git_reset_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_tostr_s (int /*<<< orphan*/ ) ; 
 int reset (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int git_reset(
	git_repository *repo,
	const git_object *target,
	git_reset_t reset_type,
	const git_checkout_options *checkout_opts)
{
	return reset(repo, target, git_oid_tostr_s(git_object_id(target)), reset_type, checkout_opts);
}