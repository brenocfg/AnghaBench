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
struct TYPE_2__ {void* cancel_baton; int /*<<< orphan*/  cancel_func; void* notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ upgrade_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_upgrade_notify_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_fs_x__with_all_locks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upgrade_body ; 

svn_error_t *
svn_fs_x__upgrade(svn_fs_t *fs,
                  svn_fs_upgrade_notify_t notify_func,
                  void *notify_baton,
                  svn_cancel_func_t cancel_func,
                  void *cancel_baton,
                  apr_pool_t *scratch_pool)
{
  upgrade_baton_t baton;
  baton.fs = fs;
  baton.notify_func = notify_func;
  baton.notify_baton = notify_baton;
  baton.cancel_func = cancel_func;
  baton.cancel_baton = cancel_baton;

  return svn_fs_x__with_all_locks(fs, upgrade_body, (void *)&baton,
                                  scratch_pool);
}