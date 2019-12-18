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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
typedef  int /*<<< orphan*/  svn_fs_x__index_info_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__close_revision_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_l2p_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_p2l_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_index_checksum (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
verify_index_checksums(svn_fs_t *fs,
                       svn_revnum_t start,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       apr_pool_t *scratch_pool)
{
  svn_fs_x__revision_file_t *rev_file;
  svn_fs_x__index_info_t l2p_index_info;
  svn_fs_x__index_info_t p2l_index_info;

  /* Open the rev / pack file and read the footer */
  SVN_ERR(svn_fs_x__rev_file_init(&rev_file, fs, start, scratch_pool));
  SVN_ERR(svn_fs_x__rev_file_l2p_info(&l2p_index_info, rev_file));
  SVN_ERR(svn_fs_x__rev_file_p2l_info(&p2l_index_info, rev_file));

  /* Verify the index contents against the checksum from the footer. */
  SVN_ERR(verify_index_checksum(rev_file, "L2P index", &l2p_index_info,
                                cancel_func, cancel_baton, scratch_pool));
  SVN_ERR(verify_index_checksum(rev_file, "P2L index", &p2l_index_info,
                                cancel_func, cancel_baton, scratch_pool));

  /* Done. */
  SVN_ERR(svn_fs_x__close_revision_file(rev_file));

  return SVN_NO_ERROR;
}