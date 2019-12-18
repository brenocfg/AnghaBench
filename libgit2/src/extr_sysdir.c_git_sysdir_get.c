#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t git_sysdir_t ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const**) ; 
 TYPE_1__* git_sysdir__dirs ; 
 int /*<<< orphan*/  git_sysdir_check_selector (size_t) ; 

int git_sysdir_get(const git_buf **out, git_sysdir_t which)
{
	assert(out);

	*out = NULL;

	GIT_ERROR_CHECK_ERROR(git_sysdir_check_selector(which));

	*out = &git_sysdir__dirs[which].buf;
	return 0;
}