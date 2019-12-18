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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_6__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int svn_boolean_t ;
struct TYPE_7__ {scalar_t__ format; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_FS_FS__MIN_PACKED_FORMAT ; 
 char const* path_rev_absolute_internal (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__is_packed_rev (TYPE_1__*,int /*<<< orphan*/ ) ; 

const char *
svn_fs_fs__path_rev_absolute(svn_fs_t *fs,
                             svn_revnum_t rev,
                             apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_boolean_t is_packed = ffd->format >= SVN_FS_FS__MIN_PACKED_FORMAT
                         && svn_fs_fs__is_packed_rev(fs, rev);

  return path_rev_absolute_internal(fs, rev, is_packed, pool);
}