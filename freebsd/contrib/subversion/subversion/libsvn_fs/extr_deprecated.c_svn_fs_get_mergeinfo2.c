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
typedef  int /*<<< orphan*/  svn_mergeinfo_inheritance_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  mergeinfo_receiver ; 
 int /*<<< orphan*/  svn_fs_get_mergeinfo3 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_get_mergeinfo2(svn_mergeinfo_catalog_t *catalog,
                      svn_fs_root_t *root,
                      const apr_array_header_t *paths,
                      svn_mergeinfo_inheritance_t inherit,
                      svn_boolean_t include_descendants,
                      svn_boolean_t adjust_inherited_mergeinfo,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  svn_mergeinfo_catalog_t result_catalog = svn_hash__make(result_pool);
  SVN_ERR(svn_fs_get_mergeinfo3(root, paths, inherit,
                                include_descendants,
                                adjust_inherited_mergeinfo,
                                mergeinfo_receiver, result_catalog,
                                scratch_pool));
  *catalog = result_catalog;

  return SVN_NO_ERROR;
}