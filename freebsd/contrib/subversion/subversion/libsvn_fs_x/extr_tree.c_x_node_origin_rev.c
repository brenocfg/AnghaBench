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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_3__ {int /*<<< orphan*/  change_set; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* svn_fs_x__dag_get_node_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_node_origin_rev(svn_revnum_t *revision,
                  svn_fs_root_t *root,
                  const char *path,
                  apr_pool_t *scratch_pool)
{
  svn_fs_x__id_t node_id;
  dag_node_t *node;

  SVN_ERR(svn_fs_x__get_temp_dag_node(&node, root, path, scratch_pool));
  node_id = *svn_fs_x__dag_get_node_id(node);

  *revision = svn_fs_x__get_revnum(node_id.change_set);

  return SVN_NO_ERROR;
}