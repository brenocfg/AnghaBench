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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int /*<<< orphan*/  base_path; int /*<<< orphan*/  pool; int /*<<< orphan*/  txn; int /*<<< orphan*/  txn_root; int /*<<< orphan*/  txn_name; int /*<<< orphan*/  revprop_table; int /*<<< orphan*/  repos; scalar_t__ txn_owner; int /*<<< orphan*/  fs; } ;
struct dir_baton {scalar_t__ base_rev; int /*<<< orphan*/  path; int /*<<< orphan*/  was_copied; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * parent; void* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct dir_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_txn_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_txn_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_prop_hash_to_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_begin_txn_for_commit2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos_fs_change_txn_props (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_root(void *edit_baton,
          svn_revnum_t base_revision,
          apr_pool_t *pool,
          void **root_baton)
{
  struct dir_baton *dirb;
  struct edit_baton *eb = edit_baton;
  svn_revnum_t youngest;

  /* We always build our transaction against HEAD.  However, we will
     sanity-check BASE_REVISION and keep it in our dir baton for out
     of dateness checks.  */
  SVN_ERR(svn_fs_youngest_rev(&youngest, eb->fs, eb->pool));

  if (base_revision > youngest)
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                             _("No such revision %ld (HEAD is %ld)"),
                             base_revision, youngest);

  /* Unless we've been instructed to use a specific transaction, we'll
     make our own. */
  if (eb->txn_owner)
    {
      SVN_ERR(svn_repos_fs_begin_txn_for_commit2(&(eb->txn),
                                                 eb->repos,
                                                 youngest,
                                                 eb->revprop_table,
                                                 eb->pool));
    }
  else /* Even if we aren't the owner of the transaction, we might
          have been instructed to set some properties. */
    {
      apr_array_header_t *props = svn_prop_hash_to_array(eb->revprop_table,
                                                         pool);
      SVN_ERR(svn_repos_fs_change_txn_props(eb->txn, props, pool));
    }
  SVN_ERR(svn_fs_txn_name(&(eb->txn_name), eb->txn, eb->pool));
  SVN_ERR(svn_fs_txn_root(&(eb->txn_root), eb->txn, eb->pool));

  /* Create a root dir baton.  The `base_path' field is an -absolute-
     path in the filesystem, upon which all further editor paths are
     based. */
  dirb = apr_pcalloc(pool, sizeof(*dirb));
  dirb->edit_baton = edit_baton;
  dirb->parent = NULL;
  dirb->pool = pool;
  dirb->was_copied = FALSE;
  dirb->path = apr_pstrdup(pool, eb->base_path);
  dirb->base_rev = base_revision;

  *root_baton = dirb;
  return SVN_NO_ERROR;
}