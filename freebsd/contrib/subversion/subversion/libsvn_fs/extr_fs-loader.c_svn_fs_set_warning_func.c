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
typedef  int /*<<< orphan*/  svn_fs_warning_callback_t ;
struct TYPE_3__ {void* warning_baton; int /*<<< orphan*/  warning; } ;
typedef  TYPE_1__ svn_fs_t ;

/* Variables and functions */

void
svn_fs_set_warning_func(svn_fs_t *fs, svn_fs_warning_callback_t warning,
                        void *warning_baton)
{
  fs->warning = warning;
  fs->warning_baton = warning_baton;
}