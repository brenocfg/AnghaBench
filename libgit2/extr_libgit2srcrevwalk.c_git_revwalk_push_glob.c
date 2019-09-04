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
typedef  int /*<<< orphan*/  git_revwalk ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int push_glob (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int git_revwalk_push_glob(git_revwalk *walk, const char *glob)
{
	assert(walk && glob);
	return push_glob(walk, glob, 0);
}