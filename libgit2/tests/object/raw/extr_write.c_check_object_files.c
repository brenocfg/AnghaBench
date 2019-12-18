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
struct TYPE_3__ {int /*<<< orphan*/  file; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ object_data ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_object_files(object_data *d)
{
   cl_assert(git_path_exists(d->dir));
   cl_assert(git_path_exists(d->file));
}