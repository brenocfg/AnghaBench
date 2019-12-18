#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_PACKED ; 
 scalar_t__ svn_fs_x__is_packed_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* svn_fs_x__path_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char const* svn_fs_x__path_rev_packed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_fs_x__path_rev_absolute(svn_fs_t *fs,
                            svn_revnum_t rev,
                            apr_pool_t *result_pool)
{
  return svn_fs_x__is_packed_rev(fs, rev)
       ? svn_fs_x__path_rev_packed(fs, rev, PATH_PACKED, result_pool)
       : svn_fs_x__path_rev(fs, rev, result_pool);
}