#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ format; int /*<<< orphan*/  min_unpacked_rev; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_PACKED_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__update_min_unpacked_rev (TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__min_unpacked_rev(svn_revnum_t *min_unpacked,
                            svn_fs_t *fs,
                            apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  /* Calling this for pre-v4 repos is illegal. */
  if (ffd->format >= SVN_FS_FS__MIN_PACKED_FORMAT)
    SVN_ERR(svn_fs_fs__update_min_unpacked_rev(fs, pool));

  *min_unpacked = ffd->min_unpacked_rev;

  return SVN_NO_ERROR;
}