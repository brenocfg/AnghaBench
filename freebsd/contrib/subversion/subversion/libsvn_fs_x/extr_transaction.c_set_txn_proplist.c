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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_props (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__write_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_txn_proplist(svn_fs_t *fs,
                 svn_fs_x__txn_id_t txn_id,
                 apr_hash_t *props,
                 apr_pool_t *scratch_pool)
{
  svn_stream_t *stream;
  const char *temp_path;

  /* Write the new contents into a temporary file. */
  SVN_ERR(svn_stream_open_unique(&stream, &temp_path,
                                 svn_fs_x__path_txn_dir(fs, txn_id,
                                                        scratch_pool),
                                 svn_io_file_del_none,
                                 scratch_pool, scratch_pool));
  SVN_ERR(svn_fs_x__write_properties(stream, props, scratch_pool));
  SVN_ERR(svn_stream_close(stream));

  /* Replace the old file with the new one. */
  SVN_ERR(svn_io_file_rename2(temp_path,
                              svn_fs_x__path_txn_props(fs, txn_id,
                                                       scratch_pool),
                              FALSE,
                              scratch_pool));

  return SVN_NO_ERROR;
}