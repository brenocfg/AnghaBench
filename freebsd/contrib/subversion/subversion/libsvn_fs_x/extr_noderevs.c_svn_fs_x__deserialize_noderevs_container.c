#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  noderevs; int /*<<< orphan*/  reps; int /*<<< orphan*/  ids; int /*<<< orphan*/  paths; } ;
typedef  TYPE_1__ svn_fs_x__noderevs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__deserialize_apr_array (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__deserialize_string_table (TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__deserialize_noderevs_container(void **out,
                                         void *data,
                                         apr_size_t data_len,
                                         apr_pool_t *result_pool)
{
  svn_fs_x__noderevs_t *noderevs = (svn_fs_x__noderevs_t *)data;

  /* de-serialize sub-structures */
  svn_fs_x__deserialize_string_table(noderevs, &noderevs->paths);
  svn_fs_x__deserialize_apr_array(noderevs, &noderevs->ids, result_pool);
  svn_fs_x__deserialize_apr_array(noderevs, &noderevs->reps, result_pool);
  svn_fs_x__deserialize_apr_array(noderevs, &noderevs->noderevs, result_pool);

  /* done */
  *out = noderevs;

  return SVN_NO_ERROR;
}