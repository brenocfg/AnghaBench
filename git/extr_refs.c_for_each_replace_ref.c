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
struct repository {int dummy; } ;
typedef  int /*<<< orphan*/  each_repo_ref_fn ;

/* Variables and functions */
 int /*<<< orphan*/  DO_FOR_EACH_INCLUDE_BROKEN ; 
 int do_for_each_repo_ref (struct repository*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  git_replace_ref_base ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int for_each_replace_ref(struct repository *r, each_repo_ref_fn fn, void *cb_data)
{
	return do_for_each_repo_ref(r, git_replace_ref_base, fn,
				    strlen(git_replace_ref_base),
				    DO_FOR_EACH_INCLUDE_BROKEN, cb_data);
}