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
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int git_diff__merge (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff__merge_like_cgit ; 

int git_diff_merge(git_diff *onto, const git_diff *from)
{
	return git_diff__merge(onto, from, git_diff__merge_like_cgit);
}