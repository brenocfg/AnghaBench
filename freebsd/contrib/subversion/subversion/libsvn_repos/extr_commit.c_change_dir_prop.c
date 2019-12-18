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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int /*<<< orphan*/  txn_root; } ;
struct dir_baton {int /*<<< orphan*/  path; scalar_t__ checked_write; int /*<<< orphan*/  base_rev; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  check_authz (struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_out_of_date (struct edit_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_authz_write ; 
 int /*<<< orphan*/  svn_fs_node_created_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/ * svn_repos_fs_change_node_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
change_dir_prop(void *dir_baton,
                const char *name,
                const svn_string_t *value,
                apr_pool_t *pool)
{
  struct dir_baton *db = dir_baton;
  struct edit_baton *eb = db->edit_baton;

  /* Check for write authorization. */
  if (!db->checked_write)
    {
      SVN_ERR(check_authz(eb, db->path, eb->txn_root,
                          svn_authz_write, pool));

      if (SVN_IS_VALID_REVNUM(db->base_rev))
        {
          /* Subversion rule:  propchanges can only happen on a directory
             which is up-to-date. */
          svn_revnum_t created_rev;
          SVN_ERR(svn_fs_node_created_rev(&created_rev,
                                          eb->txn_root, db->path, pool));

          SVN_ERR(check_out_of_date(eb, db->path, svn_node_dir,
                                    db->base_rev, created_rev));
        }

      db->checked_write = TRUE; /* Skip on further prop changes */
    }

  return svn_repos_fs_change_node_prop(eb->txn_root, db->path,
                                       name, value, pool);
}