#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_node_revision (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_check_mutable (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_fs__set_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_fs_fs__dag_get_edit_stream(svn_stream_t **contents,
                               dag_node_t *file,
                               apr_pool_t *pool)
{
  node_revision_t *noderev;
  svn_stream_t *ws;

  /* Make sure our node is a file. */
  if (file->kind != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL,
       "Attempted to set textual contents of a *non*-file node");

  /* Make sure our node is mutable. */
  if (! svn_fs_fs__dag_check_mutable(file))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       "Attempted to set textual contents of an immutable node");

  /* Get the node revision. */
  SVN_ERR(get_node_revision(&noderev, file));

  SVN_ERR(svn_fs_fs__set_contents(&ws, file->fs, noderev, pool));

  *contents = ws;

  return SVN_NO_ERROR;
}