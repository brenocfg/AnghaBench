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
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
struct TYPE_9__ {int mergeinfo_count; scalar_t__ kind; int /*<<< orphan*/  noderev_id; } ;
typedef  TYPE_2__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {TYPE_2__* node_revision; } ;
typedef  TYPE_3__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_INT64_T_FMT ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * noderev_changed (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_fs_x__dag_check_mutable (TYPE_3__*) ; 
 TYPE_1__* svn_fs_x__id_unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_fs_x__dag_increment_mergeinfo_count(dag_node_t *node,
                                        apr_int64_t increment,
                                        apr_pool_t *scratch_pool)
{
  svn_fs_x__noderev_t *noderev = node->node_revision;

  /* Sanity check: this node better be mutable! */
  if (! svn_fs_x__dag_check_mutable(node))
    {
      svn_string_t *idstr = svn_fs_x__id_unparse(&noderev->noderev_id,
                                                 scratch_pool);
      return svn_error_createf
        (SVN_ERR_FS_NOT_MUTABLE, NULL,
         "Can't increment mergeinfo count on *immutable* node-revision %s",
         idstr->data);
    }

  if (increment == 0)
    return SVN_NO_ERROR;

  noderev->mergeinfo_count += increment;
  if (noderev->mergeinfo_count < 0)
    {
      svn_string_t *idstr = svn_fs_x__id_unparse(&noderev->noderev_id,
                                                 scratch_pool);
      return svn_error_createf
        (SVN_ERR_FS_CORRUPT, NULL,
         apr_psprintf(scratch_pool,
                      _("Can't increment mergeinfo count on node-revision %%s "
                        "to negative value %%%s"),
                      APR_INT64_T_FMT),
         idstr->data, noderev->mergeinfo_count);
    }
  if (noderev->mergeinfo_count > 1 && noderev->kind == svn_node_file)
    {
      svn_string_t *idstr = svn_fs_x__id_unparse(&noderev->noderev_id,
                                                 scratch_pool);
      return svn_error_createf
        (SVN_ERR_FS_CORRUPT, NULL,
         apr_psprintf(scratch_pool,
                      _("Can't increment mergeinfo count on *file* "
                        "node-revision %%s to %%%s (> 1)"),
                      APR_INT64_T_FMT),
         idstr->data, noderev->mergeinfo_count);
    }

  /* Flush it out. */
  return noderev_changed(node, scratch_pool);
}