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
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_10__ {TYPE_1__* node_revision; } ;
typedef  TYPE_3__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  has_mergeinfo; int /*<<< orphan*/  noderev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/ * noderev_changed (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__dag_check_mutable (TYPE_3__*) ; 
 TYPE_2__* svn_fs_x__id_unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__dag_set_has_mergeinfo(dag_node_t *node,
                                svn_boolean_t has_mergeinfo,
                                apr_pool_t *scratch_pool)
{
  /* Sanity check: this node better be mutable! */
  if (! svn_fs_x__dag_check_mutable(node))
    {
      svn_string_t *idstr
        = svn_fs_x__id_unparse(&node->node_revision->noderev_id,
                               scratch_pool);
      return svn_error_createf
        (SVN_ERR_FS_NOT_MUTABLE, NULL,
         "Can't set mergeinfo flag on *immutable* node-revision %s",
         idstr->data);
    }

  node->node_revision->has_mergeinfo = has_mergeinfo;

  /* Flush it out. */
  return noderev_changed(node, scratch_pool);
}