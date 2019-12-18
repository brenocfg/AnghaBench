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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * add_excluded_or_not_present_node (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 

svn_error_t *
svn_wc__db_base_add_excluded_node(svn_wc__db_t *db,
                                  const char *local_abspath,
                                  const char *repos_relpath,
                                  const char *repos_root_url,
                                  const char *repos_uuid,
                                  svn_revnum_t revision,
                                  svn_node_kind_t kind,
                                  svn_wc__db_status_t status,
                                  const svn_skel_t *conflict,
                                  const svn_skel_t *work_items,
                                  apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT(status == svn_wc__db_status_server_excluded
                 || status == svn_wc__db_status_excluded);

  return add_excluded_or_not_present_node(
    db, local_abspath, repos_relpath, repos_root_url, repos_uuid, revision,
    kind, status, conflict, work_items, scratch_pool);
}