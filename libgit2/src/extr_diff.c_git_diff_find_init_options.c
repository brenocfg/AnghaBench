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
typedef  int /*<<< orphan*/  git_diff_find_options ;

/* Variables and functions */
 int git_diff_find_options_init (int /*<<< orphan*/ *,unsigned int) ; 

int git_diff_find_init_options(
	git_diff_find_options *opts, unsigned int version)
{
	return git_diff_find_options_init(opts, version);
}