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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* FSPATH (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  can_create (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_modify (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_root (int /*<<< orphan*/ **,struct edit_baton*) ; 
 int /*<<< orphan*/  svn_fs_close_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_copy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_delete (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_root_fs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_cb(void *baton,
        const char *src_relpath,
        svn_revnum_t src_revision,
        const char *dst_relpath,
        svn_revnum_t replaces_rev,
        apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = baton;
  const char *src_fspath = FSPATH(src_relpath, scratch_pool);
  const char *dst_fspath = FSPATH(dst_relpath, scratch_pool);
  svn_fs_root_t *root;
  svn_fs_root_t *src_root;

  SVN_ERR(get_root(&root, eb));

  /* Check if we can we replace the maybe-specified destination (revision).  */
  if (SVN_IS_VALID_REVNUM(replaces_rev))
    {
      SVN_ERR(can_modify(root, dst_fspath, replaces_rev, scratch_pool));
      SVN_ERR(svn_fs_delete(root, dst_fspath, scratch_pool));
    }
  else
    {
      SVN_ERR(can_create(root, dst_fspath, scratch_pool));
    }

  SVN_ERR(svn_fs_revision_root(&src_root, svn_fs_root_fs(root), src_revision,
                               scratch_pool));
  SVN_ERR(svn_fs_copy(src_root, src_fspath, root, dst_fspath, scratch_pool));
  svn_fs_close_root(src_root);

  return SVN_NO_ERROR;
}