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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  base_closest_copy (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base_copied_from (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__skip_ancestor (char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
prev_location(const char **prev_path,
              svn_revnum_t *prev_rev,
              svn_fs_t *fs,
              svn_fs_root_t *root,
              const char *path,
              apr_pool_t *pool)
{
  const char *copy_path, *copy_src_path, *remainder;
  svn_fs_root_t *copy_root;
  svn_revnum_t copy_src_rev;

  /* Ask about the most recent copy which affected PATH@REVISION.  If
     there was no such copy, we're done.  */
  SVN_ERR(base_closest_copy(&copy_root, &copy_path, root, path, pool));
  if (! copy_root)
    {
      *prev_rev = SVN_INVALID_REVNUM;
      *prev_path = NULL;
      return SVN_NO_ERROR;
    }

  /* Ultimately, it's not the path of the closest copy's source that
     we care about -- it's our own path's location in the copy source
     revision.  So we'll tack the relative path that expresses the
     difference between the copy destination and our path in the copy
     revision onto the copy source path to determine this information.

     In other words, if our path is "/branches/my-branch/foo/bar", and
     we know that the closest relevant copy was a copy of "/trunk" to
     "/branches/my-branch", then that relative path under the copy
     destination is "/foo/bar".  Tacking that onto the copy source
     path tells us that our path was located at "/trunk/foo/bar"
     before the copy.
  */
  SVN_ERR(base_copied_from(&copy_src_rev, &copy_src_path,
                           copy_root, copy_path, pool));
  remainder = svn_fspath__skip_ancestor(copy_path, path);
  *prev_path = svn_fspath__join(copy_src_path, remainder, pool);
  *prev_rev = copy_src_rev;
  return SVN_NO_ERROR;
}