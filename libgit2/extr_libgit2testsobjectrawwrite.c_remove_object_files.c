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
struct TYPE_3__ {int /*<<< orphan*/  dir; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ object_data ;

/* Variables and functions */
 scalar_t__ ENOTEMPTY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  odb_dir ; 
 int p_rmdir (int /*<<< orphan*/ ) ; 
 int p_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_object_files(object_data *d)
{
   cl_git_pass(p_unlink(d->file));
   cl_git_pass(p_rmdir(d->dir));
   cl_assert(errno != ENOTEMPTY);
   cl_git_pass(p_rmdir(odb_dir) < 0);
}