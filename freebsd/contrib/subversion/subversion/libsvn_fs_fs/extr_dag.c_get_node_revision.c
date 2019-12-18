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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
struct TYPE_3__ {int /*<<< orphan*/ * node_revision; int /*<<< orphan*/  node_pool; int /*<<< orphan*/  id; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__get_node_revision (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_node_revision(node_revision_t **noderev_p,
                  dag_node_t *node)
{
  /* If we've already got a copy, there's no need to read it in.  */
  if (! node->node_revision)
    {
      node_revision_t *noderev;
      apr_pool_t *scratch_pool = svn_pool_create(node->node_pool);

      SVN_ERR(svn_fs_fs__get_node_revision(&noderev, node->fs,
                                           node->id, node->node_pool,
                                           scratch_pool));
      node->node_revision = noderev;
      svn_pool_destroy(scratch_pool);
    }

  /* Now NODE->node_revision is set.  */
  *noderev_p = node->node_revision;
  return SVN_NO_ERROR;
}