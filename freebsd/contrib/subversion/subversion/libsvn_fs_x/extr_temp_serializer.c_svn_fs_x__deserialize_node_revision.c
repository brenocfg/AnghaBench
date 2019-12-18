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
typedef  int /*<<< orphan*/  svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  noderev_deserialize (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

svn_error_t *
svn_fs_x__deserialize_node_revision(void **item,
                                    void *buffer,
                                    apr_size_t buffer_size,
                                    apr_pool_t *result_pool)
{
  /* Copy the _full_ buffer as it also contains the sub-structures. */
  svn_fs_x__noderev_t *noderev = (svn_fs_x__noderev_t *)buffer;

  /* fixup of all pointers etc. */
  noderev_deserialize(noderev, &noderev);

  /* done */
  *item = noderev;
  return SVN_NO_ERROR;
}