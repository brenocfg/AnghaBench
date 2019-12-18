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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/ * predecessor_id; scalar_t__ is_fresh_txn_root; int /*<<< orphan*/  created_path; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_8__ {int /*<<< orphan*/ * fresh_root_predecessor_id; int /*<<< orphan*/  created_path; int /*<<< orphan*/  kind; int /*<<< orphan*/ * node_pool; int /*<<< orphan*/  id; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_node_revision (TYPE_1__**,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__dag_get_node(dag_node_t **node,
                        svn_fs_t *fs,
                        const svn_fs_id_t *id,
                        apr_pool_t *pool)
{
  dag_node_t *new_node;
  node_revision_t *noderev;

  /* Construct the node. */
  new_node = apr_pcalloc(pool, sizeof(*new_node));
  new_node->fs = fs;
  new_node->id = svn_fs_fs__id_copy(id, pool);

  /* Grab the contents so we can inspect the node's kind and created path. */
  new_node->node_pool = pool;
  SVN_ERR(get_node_revision(&noderev, new_node));

  /* Initialize the KIND and CREATED_PATH attributes */
  new_node->kind = noderev->kind;
  new_node->created_path = apr_pstrdup(pool, noderev->created_path);

  if (noderev->is_fresh_txn_root)
    new_node->fresh_root_predecessor_id = noderev->predecessor_id;
  else
    new_node->fresh_root_predecessor_id = NULL;

  /* Return a fresh new node */
  *node = new_node;
  return SVN_NO_ERROR;
}