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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
struct TYPE_3__ {void* cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ recover_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  recover_body ; 
 int /*<<< orphan*/ * svn_fs_x__with_all_locks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__recover(svn_fs_t *fs,
                  svn_cancel_func_t cancel_func,
                  void *cancel_baton,
                  apr_pool_t *scratch_pool)
{
  recover_baton_t b;

  /* We have no way to take out an exclusive lock in FSX, so we're
     restricted as to the types of recovery we can do.  Luckily,
     we just want to recreate the 'current' file, and we can do that just
     by blocking other writers. */
  b.fs = fs;
  b.cancel_func = cancel_func;
  b.cancel_baton = cancel_baton;
  return svn_fs_x__with_all_locks(fs, recover_body, &b, scratch_pool);
}