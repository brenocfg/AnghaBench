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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* path_txn_props (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_write2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_txn_proplist(svn_fs_t *fs,
                 const svn_fs_fs__id_part_t *txn_id,
                 apr_hash_t *props,
                 apr_pool_t *pool)
{
  svn_stream_t *tmp_stream;
  const char *tmp_path;
  const char *final_path = path_txn_props(fs, txn_id, pool);

  /* Write the new contents into a temporary file. */
  SVN_ERR(svn_stream_open_unique(&tmp_stream, &tmp_path,
                                 svn_dirent_dirname(final_path, pool),
                                 svn_io_file_del_none,
                                 pool, pool));

  /* Replace the old file with the new one. */
  SVN_ERR(svn_hash_write2(props, tmp_stream, SVN_HASH_TERMINATOR, pool));
  SVN_ERR(svn_stream_close(tmp_stream));

  SVN_ERR(svn_io_file_rename2(tmp_path, final_path, FALSE, pool));

  return SVN_NO_ERROR;
}