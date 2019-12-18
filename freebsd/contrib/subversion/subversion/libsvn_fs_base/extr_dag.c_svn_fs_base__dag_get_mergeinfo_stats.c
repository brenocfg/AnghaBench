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
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  mergeinfo_count; int /*<<< orphan*/  has_mergeinfo; } ;
typedef  TYPE_1__ node_revision_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__dag_get_mergeinfo_stats(svn_boolean_t *has_mergeinfo,
                                     apr_int64_t *count,
                                     dag_node_t *node,
                                     trail_t *trail,
                                     apr_pool_t *pool)
{
  node_revision_t *node_rev;
  svn_fs_t *fs = svn_fs_base__dag_get_fs(node);
  const svn_fs_id_t *id = svn_fs_base__dag_get_id(node);

  SVN_ERR(svn_fs_bdb__get_node_revision(&node_rev, fs, id, trail, pool));
  if (has_mergeinfo)
    *has_mergeinfo = node_rev->has_mergeinfo;
  if (count)
    *count = node_rev->mergeinfo_count;
  return SVN_NO_ERROR;
}