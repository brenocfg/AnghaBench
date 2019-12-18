#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_freeze_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct fs_freeze_baton_t {void* freeze_baton; int /*<<< orphan*/  freeze_func; TYPE_1__* fs; } ;
struct TYPE_7__ {scalar_t__ format; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_PACK_LOCK_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fs_freeze_body2 (struct fs_freeze_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__check_fs (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__with_pack_lock (TYPE_1__*,int /*<<< orphan*/  (*) (struct fs_freeze_baton_t*,int /*<<< orphan*/ *),struct fs_freeze_baton_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_freeze(svn_fs_t *fs,
          svn_fs_freeze_func_t freeze_func,
          void *freeze_baton,
          apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  struct fs_freeze_baton_t b;

  b.fs = fs;
  b.freeze_func = freeze_func;
  b.freeze_baton = freeze_baton;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  if (ffd->format >= SVN_FS_FS__MIN_PACK_LOCK_FORMAT)
    SVN_ERR(svn_fs_fs__with_pack_lock(fs, fs_freeze_body2, &b, pool));
  else
    SVN_ERR(fs_freeze_body2(&b, pool));

  return SVN_NO_ERROR;
}