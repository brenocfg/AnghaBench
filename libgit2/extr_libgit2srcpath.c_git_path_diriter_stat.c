#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_5__ {TYPE_1__ path; } ;
typedef  TYPE_2__ git_path_diriter ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int git_path_lstat (int /*<<< orphan*/ ,struct stat*) ; 

int git_path_diriter_stat(struct stat *out, git_path_diriter *diriter)
{
	assert(out && diriter);

	return git_path_lstat(diriter->path.ptr, out);
}