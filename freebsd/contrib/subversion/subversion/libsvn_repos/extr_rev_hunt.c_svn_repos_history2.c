#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  TYPE_1__* (* svn_repos_history_func_t ) (void*,char const*,scalar_t__,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  (* svn_repos_authz_func_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_history_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_UNREADABLE ; 
 scalar_t__ SVN_ERR_CEASE_INVOCATION ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_history_location (char const**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_history_prev2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_history2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_history2(svn_fs_t *fs,
                   const char *path,
                   svn_repos_history_func_t history_func,
                   void *history_baton,
                   svn_repos_authz_func_t authz_read_func,
                   void *authz_read_baton,
                   svn_revnum_t start,
                   svn_revnum_t end,
                   svn_boolean_t cross_copies,
                   apr_pool_t *pool)
{
  svn_fs_history_t *history;
  apr_pool_t *oldpool = svn_pool_create(pool);
  apr_pool_t *newpool = svn_pool_create(pool);
  const char *history_path;
  svn_revnum_t history_rev;
  svn_fs_root_t *root;

  /* Validate the revisions. */
  if (! SVN_IS_VALID_REVNUM(start))
    return svn_error_createf
      (SVN_ERR_FS_NO_SUCH_REVISION, 0,
       _("Invalid start revision %ld"), start);
  if (! SVN_IS_VALID_REVNUM(end))
    return svn_error_createf
      (SVN_ERR_FS_NO_SUCH_REVISION, 0,
       _("Invalid end revision %ld"), end);

  /* Ensure that the input is ordered. */
  if (start > end)
    {
      svn_revnum_t tmprev = start;
      start = end;
      end = tmprev;
    }

  /* Get a revision root for END, and an initial HISTORY baton.  */
  SVN_ERR(svn_fs_revision_root(&root, fs, end, pool));

  if (authz_read_func)
    {
      svn_boolean_t readable;
      SVN_ERR(authz_read_func(&readable, root, path,
                              authz_read_baton, pool));
      if (! readable)
        return svn_error_create(SVN_ERR_AUTHZ_UNREADABLE, NULL, NULL);
    }

  SVN_ERR(svn_fs_node_history2(&history, root, path, oldpool, oldpool));

  /* Now, we loop over the history items, calling svn_fs_history_prev(). */
  do
    {
      /* Note that we have to do some crazy pool work here.  We can't
         get rid of the old history until we use it to get the new, so
         we alternate back and forth between our subpools.  */
      apr_pool_t *tmppool;
      svn_error_t *err;

      SVN_ERR(svn_fs_history_prev2(&history, history, cross_copies, newpool,
                                   oldpool));

      /* Only continue if there is further history to deal with. */
      if (! history)
        break;

      /* Fetch the location information for this history step. */
      SVN_ERR(svn_fs_history_location(&history_path, &history_rev,
                                      history, newpool));

      /* If this history item predates our START revision, quit
         here. */
      if (history_rev < start)
        break;

      /* Is the history item readable?  If not, quit. */
      if (authz_read_func)
        {
          svn_boolean_t readable;
          svn_fs_root_t *history_root;
          SVN_ERR(svn_fs_revision_root(&history_root, fs,
                                       history_rev, newpool));
          SVN_ERR(authz_read_func(&readable, history_root, history_path,
                                  authz_read_baton, newpool));
          if (! readable)
            break;
        }

      /* Call the user-provided callback function. */
      err = history_func(history_baton, history_path, history_rev, newpool);
      if (err)
        {
          if (err->apr_err == SVN_ERR_CEASE_INVOCATION)
            {
              svn_error_clear(err);
              goto cleanup;
            }
          else
            {
              return svn_error_trace(err);
            }
        }

      /* We're done with the old history item, so we can clear its
         pool, and then toggle our notion of "the old pool". */
      svn_pool_clear(oldpool);
      tmppool = oldpool;
      oldpool = newpool;
      newpool = tmppool;
    }
  while (history); /* shouldn't hit this */

 cleanup:
  svn_pool_destroy(oldpool);
  svn_pool_destroy(newpool);
  return SVN_NO_ERROR;
}