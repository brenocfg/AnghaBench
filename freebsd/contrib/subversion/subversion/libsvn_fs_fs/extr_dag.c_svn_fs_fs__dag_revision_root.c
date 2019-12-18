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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {char* created_path; int /*<<< orphan*/ * fresh_root_predecessor_id; int /*<<< orphan*/  kind; int /*<<< orphan*/ * node_pool; int /*<<< orphan*/  id; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_fs__rev_get_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 

svn_error_t *
svn_fs_fs__dag_revision_root(dag_node_t **node_p,
                             svn_fs_t *fs,
                             svn_revnum_t rev,
                             apr_pool_t *pool)
{
  dag_node_t *new_node;

  /* Construct the node. */
  new_node = apr_pcalloc(pool, sizeof(*new_node));
  new_node->fs = fs;
  SVN_ERR(svn_fs_fs__rev_get_root(&new_node->id, fs, rev, pool, pool));

  /* Grab the contents so we can inspect the node's kind and created path. */
  new_node->node_pool = pool;

  /* Initialize the KIND and CREATED_PATH attributes */
  new_node->kind = svn_node_dir;
  new_node->created_path = "/";
  new_node->fresh_root_predecessor_id = NULL;

  /* Return a fresh new node */
  *node_p = new_node;
  return SVN_NO_ERROR;
}