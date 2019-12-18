#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  path; TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_t ;
struct TYPE_10__ {int /*<<< orphan*/  fs_type; } ;
typedef  TYPE_3__ svn_fs_info_placeholder_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* info_fsap ) (void const**,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_3__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (void const**,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_info(const svn_fs_info_placeholder_t **info_p,
            svn_fs_t *fs,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  if (fs->vtable->info_fsap)
    {
      SVN_ERR(fs->vtable->info_fsap((const void **)info_p, fs,
                                    result_pool, scratch_pool));
    }
  else
    {
      svn_fs_info_placeholder_t *info = apr_palloc(result_pool, sizeof(*info));
      /* ### Ask the disk(!), since svn_fs_t doesn't cache the answer. */
      SVN_ERR(svn_fs_type(&info->fs_type, fs->path, result_pool));
      *info_p = info;
    }
  return SVN_NO_ERROR;
}