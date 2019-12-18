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
struct TYPE_6__ {int /*<<< orphan*/ * copies; void* base_id; void* root_id; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  predecessor_id; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_fs__get_node_revision (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_fs_fs__id_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_txn_create_root (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__get_txn(transaction_t **txn_p,
                   svn_fs_t *fs,
                   const svn_fs_fs__id_part_t *txn_id,
                   apr_pool_t *pool)
{
  transaction_t *txn;
  node_revision_t *noderev;
  svn_fs_id_t *root_id;

  txn = apr_pcalloc(pool, sizeof(*txn));
  root_id = svn_fs_fs__id_txn_create_root(txn_id, pool);

  SVN_ERR(svn_fs_fs__get_node_revision(&noderev, fs, root_id, pool, pool));

  txn->root_id = svn_fs_fs__id_copy(noderev->id, pool);
  txn->base_id = svn_fs_fs__id_copy(noderev->predecessor_id, pool);
  txn->copies = NULL;

  *txn_p = txn;

  return SVN_NO_ERROR;
}