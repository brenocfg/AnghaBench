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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  txn_number; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ get_and_increment_txn_key_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_and_increment_txn_key_body ; 
 char* svn_fs_x__txn_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__with_txn_current_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_txn_dir(const char **id_p,
               svn_fs_x__txn_id_t *txn_id,
               svn_fs_t *fs,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  get_and_increment_txn_key_baton_t cb;

  /* Get the current transaction sequence value, which is a base-36
    number, from the txn-current file, and write an
    incremented value back out to the file.  Place the revision
    number the transaction is based off into the transaction id. */
  cb.fs = fs;
  SVN_ERR(svn_fs_x__with_txn_current_lock(fs,
                                          get_and_increment_txn_key_body,
                                          &cb,
                                          scratch_pool));
  *txn_id = cb.txn_number;
  *id_p = svn_fs_x__txn_name(*txn_id, result_pool);

  return SVN_NO_ERROR;
}