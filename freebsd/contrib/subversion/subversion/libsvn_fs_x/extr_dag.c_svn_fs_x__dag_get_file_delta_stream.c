#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  fs; TYPE_1__* node_revision; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_fs_x__get_file_delta_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_fs_x__dag_get_file_delta_stream(svn_txdelta_stream_t **stream_p,
                                    dag_node_t *source,
                                    dag_node_t *target,
                                    apr_pool_t *result_pool,
                                    apr_pool_t *scratch_pool)
{
  svn_fs_x__noderev_t *src_noderev = source ? source->node_revision : NULL;
  svn_fs_x__noderev_t *tgt_noderev = target->node_revision;

  /* Make sure our nodes are files. */
  if ((source && src_noderev->kind != svn_node_file)
      || tgt_noderev->kind != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL,
       "Attempted to get textual contents of a *non*-file node");

  /* Get the delta stream. */
  return svn_fs_x__get_file_delta_stream(stream_p, target->fs,
                                         src_noderev, tgt_noderev,
                                         result_pool, scratch_pool);
}