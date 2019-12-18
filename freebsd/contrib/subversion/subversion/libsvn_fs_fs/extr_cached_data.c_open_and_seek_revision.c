#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_5__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  aligned_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__ensure_revision_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__item_offset (int*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__open_pack_or_rev_file (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_and_seek_revision(svn_fs_fs__revision_file_t **file,
                       svn_fs_t *fs,
                       svn_revnum_t rev,
                       apr_uint64_t item,
                       apr_pool_t *pool)
{
  svn_fs_fs__revision_file_t *rev_file;
  apr_off_t offset = -1;

  SVN_ERR(svn_fs_fs__ensure_revision_exists(rev, fs, pool));

  SVN_ERR(svn_fs_fs__open_pack_or_rev_file(&rev_file, fs, rev, pool, pool));
  SVN_ERR(svn_fs_fs__item_offset(&offset, fs, rev_file, rev, NULL, item,
                                 pool));

  SVN_ERR(aligned_seek(fs, rev_file->file, NULL, offset, pool));

  *file = rev_file;

  return SVN_NO_ERROR;
}