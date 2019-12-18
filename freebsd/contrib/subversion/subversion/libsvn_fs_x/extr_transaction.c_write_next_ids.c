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
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_TRUNCATE ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/  svn__ui64tobase36 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_next_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_next_ids(svn_fs_t *fs,
               svn_fs_x__txn_id_t txn_id,
               apr_uint64_t node_id,
               apr_uint64_t copy_id,
               apr_pool_t *scratch_pool)
{
  apr_file_t *file;
  char buffer[2 * SVN_INT64_BUFFER_SIZE + 2];
  char *p = buffer;

  p += svn__ui64tobase36(p, node_id);
  *(p++) = ' ';
  p += svn__ui64tobase36(p, copy_id);
  *(p++) = '\n';
  *(p++) = '\0';

  SVN_ERR(svn_io_file_open(&file,
                           svn_fs_x__path_txn_next_ids(fs, txn_id,
                                                       scratch_pool),
                           APR_WRITE | APR_TRUNCATE,
                           APR_OS_DEFAULT, scratch_pool));
  SVN_ERR(svn_io_file_write_full(file, buffer, p - buffer, NULL,
                                 scratch_pool));
  return svn_io_file_close(file, scratch_pool);
}