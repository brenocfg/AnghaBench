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
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_file_delta_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_temp_dag_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_get_file_delta_stream(svn_txdelta_stream_t **stream_p,
                        svn_fs_root_t *source_root,
                        const char *source_path,
                        svn_fs_root_t *target_root,
                        const char *target_path,
                        apr_pool_t *pool)
{
  dag_node_t *source_node, *target_node;
  apr_pool_t *scratch_pool = svn_pool_create(pool);

  if (source_root && source_path)
    SVN_ERR(svn_fs_x__get_dag_node(&source_node, source_root, source_path,
                                   scratch_pool, scratch_pool));
  else
    source_node = NULL;
  SVN_ERR(svn_fs_x__get_temp_dag_node(&target_node, target_root, target_path,
                                      scratch_pool));

  /* Create a delta stream that turns the source into the target.  */
  SVN_ERR(svn_fs_x__dag_get_file_delta_stream(stream_p, source_node,
                                              target_node, pool,
                                              scratch_pool));

  svn_pool_destroy(scratch_pool);
  return SVN_NO_ERROR;
}