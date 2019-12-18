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
typedef  int /*<<< orphan*/  svn_repos_authz_access_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int /*<<< orphan*/  txn_root; int /*<<< orphan*/  base_path; } ;
struct dir_baton {char const* path; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_authz (struct edit_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_out_of_date (struct edit_baton*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_of_date (char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_authz_recursive ; 
 int /*<<< orphan*/  svn_authz_write ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_delete (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_created_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
delete_entry(const char *path,
             svn_revnum_t revision,
             void *parent_baton,
             apr_pool_t *pool)
{
  struct dir_baton *parent = parent_baton;
  struct edit_baton *eb = parent->edit_baton;
  svn_node_kind_t kind;
  svn_repos_authz_access_t required = svn_authz_write;
  const char *full_path;

  full_path = svn_fspath__join(eb->base_path,
                               svn_relpath_canonicalize(path, pool), pool);

  /* Check PATH in our transaction.  */
  SVN_ERR(svn_fs_check_path(&kind, eb->txn_root, full_path, pool));

  /* Deletion requires a recursive write access, as well as write
     access to the parent directory. */
  if (kind == svn_node_dir)
    required |= svn_authz_recursive;
  SVN_ERR(check_authz(eb, full_path, eb->txn_root,
                      required, pool));
  SVN_ERR(check_authz(eb, parent->path, eb->txn_root,
                      svn_authz_write, pool));

  /* If PATH doesn't exist in the txn, the working copy is out of date. */
  if (kind == svn_node_none)
    return svn_error_trace(out_of_date(full_path, kind));

  /* Now, make sure we're deleting the node we *think* we're
     deleting, else return an out-of-dateness error. */
  if (SVN_IS_VALID_REVNUM(revision))
    {
      svn_revnum_t cr_rev;

      SVN_ERR(svn_fs_node_created_rev(&cr_rev, eb->txn_root, full_path, pool));
      SVN_ERR(check_out_of_date(eb, full_path, kind, revision, cr_rev));
    }

  /* This routine is a mindless wrapper.  We call svn_fs_delete()
     because that will delete files and recursively delete
     directories.  */
  return svn_error_trace(svn_fs_delete(eb->txn_root, full_path, pool));
}