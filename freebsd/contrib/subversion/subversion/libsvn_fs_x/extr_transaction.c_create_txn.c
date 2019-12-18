#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
struct TYPE_4__ {TYPE_2__* fsap_data; int /*<<< orphan*/ * vtable; int /*<<< orphan*/  base_rev; int /*<<< orphan*/ * fs; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_2__ fs_txn_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_new_txn_noderev_from_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_txn_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__ensure_revision_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__init_rev_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_changes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_next_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_proto_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_proto_rev_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_vtable ; 

__attribute__((used)) static svn_error_t *
create_txn(svn_fs_txn_t **txn_p,
           svn_fs_t *fs,
           svn_revnum_t rev,
           apr_pool_t *result_pool,
           apr_pool_t *scratch_pool)
{
  svn_fs_txn_t *txn;
  fs_txn_data_t *ftd;
  svn_fs_x__id_t root_id;

  txn = apr_pcalloc(result_pool, sizeof(*txn));
  ftd = apr_pcalloc(result_pool, sizeof(*ftd));

  /* Valid revision number? */
  SVN_ERR(svn_fs_x__ensure_revision_exists(rev, fs, scratch_pool));

  /* Get the txn_id. */
  SVN_ERR(create_txn_dir(&txn->id, &ftd->txn_id, fs, result_pool,
                         scratch_pool));

  txn->fs = fs;
  txn->base_rev = rev;

  txn->vtable = &txn_vtable;
  txn->fsap_data = ftd;
  *txn_p = txn;

  /* Create a new root node for this transaction. */
  svn_fs_x__init_rev_root(&root_id, rev);
  SVN_ERR(create_new_txn_noderev_from_rev(fs, ftd->txn_id, &root_id,
                                          scratch_pool));

  /* Create an empty rev file. */
  SVN_ERR(svn_io_file_create_empty(
              svn_fs_x__path_txn_proto_rev(fs, ftd->txn_id, scratch_pool),
              scratch_pool));

  /* Create an empty rev-lock file. */
  SVN_ERR(svn_io_file_create_empty(
              svn_fs_x__path_txn_proto_rev_lock(fs, ftd->txn_id, scratch_pool),
              scratch_pool));

  /* Create an empty changes file. */
  SVN_ERR(svn_io_file_create_empty(
              svn_fs_x__path_txn_changes(fs, ftd->txn_id, scratch_pool),
              scratch_pool));

  /* Create the next-ids file. */
  SVN_ERR(svn_io_file_create(
              svn_fs_x__path_txn_next_ids(fs, ftd->txn_id, scratch_pool),
              "0 0\n", scratch_pool));

  return SVN_NO_ERROR;
}