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
typedef  int /*<<< orphan*/  svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__p2l_proto_index_add_entry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__p2l_proto_index_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_p2l_proto_index (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__use_log_addressing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
store_p2l_index_entry(svn_fs_t *fs,
                      const svn_fs_fs__id_part_t *txn_id,
                      const svn_fs_fs__p2l_entry_t *entry,
                      apr_pool_t *pool)
{
  const char *path;
  apr_file_t *file;

  SVN_ERR_ASSERT(svn_fs_fs__use_log_addressing(fs));

  path = svn_fs_fs__path_p2l_proto_index(fs, txn_id, pool);
  SVN_ERR(svn_fs_fs__p2l_proto_index_open(&file, path, pool));
  SVN_ERR(svn_fs_fs__p2l_proto_index_add_entry(file, entry, pool));
  SVN_ERR(svn_io_file_close(file, pool));

  return SVN_NO_ERROR;
}