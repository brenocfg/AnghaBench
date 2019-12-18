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
struct TYPE_3__ {void* freeze_baton; int /*<<< orphan*/  freeze_func; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ x_freeze_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_freeze_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__with_pack_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x_freeze_body2 ; 

__attribute__((used)) static svn_error_t *
x_freeze(svn_fs_t *fs,
         svn_fs_freeze_func_t freeze_func,
         void *freeze_baton,
         apr_pool_t *scratch_pool)
{
  x_freeze_baton_t b;

  b.fs = fs;
  b.freeze_func = freeze_func;
  b.freeze_baton = freeze_baton;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));
  SVN_ERR(svn_fs_x__with_pack_lock(fs, x_freeze_body2, &b, scratch_pool));

  return SVN_NO_ERROR;
}