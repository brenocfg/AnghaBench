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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_iterator_flag_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_ITERATOR_IGNORE_CASE ; 
 int GIT_PATHSPEC_IGNORE_CASE ; 
 int GIT_PATHSPEC_USE_CASE ; 

__attribute__((used)) static git_iterator_flag_t pathspec_match_iter_flags(uint32_t flags)
{
	git_iterator_flag_t f = 0;

	if ((flags & GIT_PATHSPEC_IGNORE_CASE) != 0)
		f |= GIT_ITERATOR_IGNORE_CASE;
	else if ((flags & GIT_PATHSPEC_USE_CASE) != 0)
		f |= GIT_ITERATOR_DONT_IGNORE_CASE;

	return f;
}