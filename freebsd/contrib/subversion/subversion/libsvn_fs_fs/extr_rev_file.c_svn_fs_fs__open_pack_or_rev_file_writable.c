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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_revision_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_pack_or_rev_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_fs__open_pack_or_rev_file_writable(svn_fs_fs__revision_file_t** file,
                                          svn_fs_t* fs,
                                          svn_revnum_t rev,
                                          apr_pool_t* result_pool,
                                          apr_pool_t *scratch_pool)
{
  *file = apr_palloc(result_pool, sizeof(**file));
  init_revision_file(*file, fs, rev, result_pool);

  return svn_error_trace(open_pack_or_rev_file(*file, fs, rev, TRUE,
                                               result_pool, scratch_pool));
}