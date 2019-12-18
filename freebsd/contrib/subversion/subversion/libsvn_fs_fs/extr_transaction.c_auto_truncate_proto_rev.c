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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_INDEX_INCONSISTENT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_off_t_toa (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__p2l_proto_index_next_offset (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__p2l_proto_index_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_p2l_proto_index (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__use_log_addressing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_trunc (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
auto_truncate_proto_rev(svn_fs_t *fs,
                        apr_file_t *proto_rev,
                        apr_off_t actual_length,
                        const svn_fs_fs__id_part_t *txn_id,
                        apr_pool_t *pool)
{
  /* Only relevant for newer FSFS formats. */
  if (svn_fs_fs__use_log_addressing(fs))
    {
      /* Determine file range covered by the proto-index so far.  Note that
         we always append to both file, i.e. the last index entry also
         corresponds to the last addition in the rev file. */
      const char *path = svn_fs_fs__path_p2l_proto_index(fs, txn_id, pool);
      apr_file_t *file;
      apr_off_t indexed_length;

      SVN_ERR(svn_fs_fs__p2l_proto_index_open(&file, path, pool));
      SVN_ERR(svn_fs_fs__p2l_proto_index_next_offset(&indexed_length, file,
                                                     pool));
      SVN_ERR(svn_io_file_close(file, pool));

      /* Handle mismatches. */
      if (indexed_length < actual_length)
        SVN_ERR(svn_io_file_trunc(proto_rev, indexed_length, pool));
      else if (indexed_length > actual_length)
        return svn_error_createf(SVN_ERR_FS_INDEX_INCONSISTENT,
                                 NULL,
                                 _("p2l proto index offset %s beyond proto"
                                   "rev file size %s for TXN %s"),
                                   apr_off_t_toa(pool, indexed_length),
                                   apr_off_t_toa(pool, actual_length),
                                   svn_fs_fs__id_txn_unparse(txn_id, pool));
    }

  return SVN_NO_ERROR;
}