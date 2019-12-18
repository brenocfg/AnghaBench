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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  data_rep; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_7__ {scalar_t__ kind; int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_node_revision (TYPE_1__**,TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_fs__get_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_fs_fs__dag_get_contents(svn_stream_t **contents_p,
                            dag_node_t *file,
                            apr_pool_t *pool)
{
  node_revision_t *noderev;
  svn_stream_t *contents;

  /* Make sure our node is a file. */
  if (file->kind != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL,
       "Attempted to get textual contents of a *non*-file node");

  /* Go get a fresh node-revision for FILE. */
  SVN_ERR(get_node_revision(&noderev, file));

  /* Get a stream to the contents. */
  SVN_ERR(svn_fs_fs__get_contents(&contents, file->fs,
                                  noderev->data_rep, TRUE, pool));

  *contents_p = contents;

  return SVN_NO_ERROR;
}