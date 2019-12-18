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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__noderev_deserialize (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

svn_error_t *
svn_fs_fs__deserialize_node_revision(void **item,
                                     void *buffer,
                                     apr_size_t buffer_size,
                                     apr_pool_t *pool)
{
  /* Copy the _full_ buffer as it also contains the sub-structures. */
  node_revision_t *noderev = (node_revision_t *)buffer;

  /* fixup of all pointers etc. */
  svn_fs_fs__noderev_deserialize(noderev, &noderev);

  /* done */
  *item = noderev;
  return SVN_NO_ERROR;
}