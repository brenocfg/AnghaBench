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

/* Variables and functions */
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll_user_merge ; 
 int /*<<< orphan*/ * ll_user_merge_tail ; 
 int /*<<< orphan*/  read_merge_config ; 

__attribute__((used)) static void initialize_ll_merge(void)
{
	if (ll_user_merge_tail)
		return;
	ll_user_merge_tail = &ll_user_merge;
	git_config(read_merge_config, NULL);
}