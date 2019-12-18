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
typedef  int /*<<< orphan*/  git_diff_delta ;

/* Variables and functions */
 char const* diff_delta__path (int /*<<< orphan*/  const*) ; 

const char *git_diff_delta__path(const git_diff_delta *delta)
{
	return diff_delta__path(delta);
}