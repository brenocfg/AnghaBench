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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_3__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_next_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__change_set_by_txn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_next_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__reserve_copy_id(svn_fs_x__id_t *copy_id_p,
                          svn_fs_t *fs,
                          svn_fs_x__txn_id_t txn_id,
                          apr_pool_t *scratch_pool)
{
  apr_uint64_t node_id, copy_id;

  /* First read in the current next-ids file. */
  SVN_ERR(read_next_ids(&node_id, &copy_id, fs, txn_id, scratch_pool));

  copy_id_p->change_set = svn_fs_x__change_set_by_txn(txn_id);
  copy_id_p->number = copy_id;

  SVN_ERR(write_next_ids(fs, txn_id, node_id, ++copy_id, scratch_pool));

  return SVN_NO_ERROR;
}