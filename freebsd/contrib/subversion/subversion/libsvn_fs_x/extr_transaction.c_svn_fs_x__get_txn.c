#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_8__ {int /*<<< orphan*/ * copies; int /*<<< orphan*/  base_rev; } ;
typedef  TYPE_2__ svn_fs_x__transaction_t ;
struct TYPE_7__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_9__ {TYPE_1__ predecessor_id; } ;
typedef  TYPE_3__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_x__get_node_revision (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__init_txn_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__get_txn(svn_fs_x__transaction_t **txn_p,
                  svn_fs_t *fs,
                  svn_fs_x__txn_id_t txn_id,
                  apr_pool_t *pool)
{
  svn_fs_x__transaction_t *txn;
  svn_fs_x__noderev_t *noderev;
  svn_fs_x__id_t root_id;

  txn = apr_pcalloc(pool, sizeof(*txn));
  svn_fs_x__init_txn_root(&root_id, txn_id);

  SVN_ERR(svn_fs_x__get_node_revision(&noderev, fs, &root_id, pool, pool));

  txn->base_rev = svn_fs_x__get_revnum(noderev->predecessor_id.change_set);
  txn->copies = NULL;

  *txn_p = txn;

  return SVN_NO_ERROR;
}