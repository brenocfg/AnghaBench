#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  checkout_data ;

/* Variables and functions */
 scalar_t__ checkout_target_fullpath (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 
 int git_path_is_empty_dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool checkout_is_empty_dir(checkout_data *data, const char *path)
{
	git_buf *fullpath;

	if (checkout_target_fullpath(&fullpath, data, path) < 0)
		return false;

	return git_path_is_empty_dir(fullpath->ptr);
}