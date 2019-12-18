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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int git_submodule__open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 

int git_submodule_open(git_repository **subrepo, git_submodule *sm)
{
	return git_submodule__open(subrepo, sm, false);
}