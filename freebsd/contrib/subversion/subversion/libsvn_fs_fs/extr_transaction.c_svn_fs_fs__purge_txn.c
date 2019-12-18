#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ format; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_PROTOREVS_DIR_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  purge_shared_txn (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_parse (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_dir (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_proto_rev (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_proto_rev_lock (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__purge_txn(svn_fs_t *fs,
                     const char *txn_id_str,
                     apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_fs_fs__id_part_t txn_id;
  SVN_ERR(svn_fs_fs__id_txn_parse(&txn_id, txn_id_str));

  /* Remove the shared transaction object associated with this transaction. */
  SVN_ERR(purge_shared_txn(fs, &txn_id, pool));
  /* Remove the directory associated with this transaction. */
  SVN_ERR(svn_io_remove_dir2(svn_fs_fs__path_txn_dir(fs, &txn_id, pool),
                             FALSE, NULL, NULL, pool));
  if (ffd->format >= SVN_FS_FS__MIN_PROTOREVS_DIR_FORMAT)
    {
      /* Delete protorev and its lock, which aren't in the txn
         directory.  It's OK if they don't exist (for example, if this
         is post-commit and the proto-rev has been moved into
         place). */
      SVN_ERR(svn_io_remove_file2(
                  svn_fs_fs__path_txn_proto_rev(fs, &txn_id, pool),
                  TRUE, pool));
      SVN_ERR(svn_io_remove_file2(
                  svn_fs_fs__path_txn_proto_rev_lock(fs, &txn_id, pool),
                  TRUE, pool));
    }
  return SVN_NO_ERROR;
}