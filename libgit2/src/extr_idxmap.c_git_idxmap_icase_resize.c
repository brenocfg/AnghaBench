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
typedef  int /*<<< orphan*/  khiter_t ;
typedef  int /*<<< orphan*/  git_idxmap_icase ;

/* Variables and functions */
 int /*<<< orphan*/  git__is_uint32 (size_t) ; 
 int /*<<< orphan*/  git_error_set_oom () ; 
 int /*<<< orphan*/  idxicase ; 
 scalar_t__ kh_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_idxmap_icase_resize(git_idxmap_icase *map, size_t size)
{
	if (!git__is_uint32(size) ||
	    kh_resize(idxicase, map, (khiter_t)size) < 0) {
		git_error_set_oom();
		return -1;
	}
	return 0;
}