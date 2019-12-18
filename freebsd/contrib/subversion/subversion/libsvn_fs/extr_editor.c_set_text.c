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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_apply_text (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_text(svn_fs_root_t *root,
         const char *fspath,
         const svn_checksum_t *checksum,
         svn_stream_t *contents,
         svn_cancel_func_t cancel_func,
         void *cancel_baton,
         apr_pool_t *scratch_pool)
{
  svn_stream_t *fs_contents;

  /* ### We probably don't have an MD5 checksum, so no digest is available
     ### for svn_fs_apply_text() to validate. It would be nice to have an
     ### FS API that takes our CHECKSUM/CONTENTS pair (and PROPS!).  */
  SVN_ERR(svn_fs_apply_text(&fs_contents, root, fspath,
                            NULL /* result_checksum */,
                            scratch_pool));
  SVN_ERR(svn_stream_copy3(contents, fs_contents,
                           cancel_func, cancel_baton,
                           scratch_pool));

  return SVN_NO_ERROR;
}