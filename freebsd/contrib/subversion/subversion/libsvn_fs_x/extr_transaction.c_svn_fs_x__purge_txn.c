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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  purge_shared_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_proto_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_proto_rev_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__txn_by_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__purge_txn(svn_fs_t *fs,
                    const char *txn_id_str,
                    apr_pool_t *scratch_pool)
{
  svn_fs_x__txn_id_t txn_id;

  /* The functions we are calling open files and operate on the OS FS.
     Since these may allocate a non-trivial amount of memory, do that
     in a SUBPOOL and clear that one up before returning. */
  apr_pool_t *subpool = svn_pool_create(scratch_pool);
  SVN_ERR(svn_fs_x__txn_by_name(&txn_id, txn_id_str));

  /* Remove the shared transaction object associated with this transaction. */
  SVN_ERR(purge_shared_txn(fs, txn_id, subpool));
  /* Remove the directory associated with this transaction. */
  SVN_ERR(svn_io_remove_dir2(svn_fs_x__path_txn_dir(fs, txn_id, subpool),
                             FALSE, NULL, NULL, subpool));

  /* Delete protorev and its lock, which aren't in the txn directory.
     It's OK if they don't exist (for example, if this is post-commit
     and the proto-rev has been moved into place). */
  SVN_ERR(svn_io_remove_file2(
                svn_fs_x__path_txn_proto_rev(fs, txn_id, subpool),
                TRUE, subpool));
  SVN_ERR(svn_io_remove_file2(
                svn_fs_x__path_txn_proto_rev_lock(fs, txn_id, subpool),
                TRUE, subpool));

  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}