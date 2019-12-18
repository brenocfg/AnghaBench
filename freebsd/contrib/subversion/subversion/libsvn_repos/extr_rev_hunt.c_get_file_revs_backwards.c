#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  (* svn_repos_authz_func_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_file_rev_handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct send_baton {int /*<<< orphan*/ * iterpool; int /*<<< orphan*/ * last_pool; int /*<<< orphan*/  last_props; int /*<<< orphan*/ * last_path; int /*<<< orphan*/ * last_root; void* include_merged_revisions; } ;
struct path_revision {char const* path; scalar_t__ revnum; void* merged; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 struct path_revision* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_path_revision (struct path_revision*,TYPE_1__*,struct send_baton*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_history_location (char const**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_history_prev2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_history2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 void* svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_file_revs_backwards(svn_repos_t *repos,
                        const char *path,
                        svn_revnum_t start,
                        svn_revnum_t end,
                        svn_repos_authz_func_t authz_read_func,
                        void *authz_read_baton,
                        svn_file_rev_handler_t handler,
                        void *handler_baton,
                        apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool, *last_pool;
  svn_fs_history_t *history;
  svn_fs_root_t *root;
  svn_node_kind_t kind;
  struct send_baton sb;

  /* We switch between two pools while looping and so does the path-rev
     handler for actually reported revisions. We do this as we
     need just information from last iteration to be available. */

  iterpool = svn_pool_create(scratch_pool);
  last_pool = svn_pool_create(scratch_pool);
  sb.iterpool = svn_pool_create(scratch_pool);
  sb.last_pool = svn_pool_create(scratch_pool);
  sb.include_merged_revisions = FALSE;

  /* We want the first txdelta to be against the empty file. */
  sb.last_root = NULL;
  sb.last_path = NULL;

  /* Create an empty hash table for the first property diff. */
  sb.last_props = apr_hash_make(sb.last_pool);

  /* The path had better be a file in this revision. */
  SVN_ERR(svn_fs_revision_root(&root, repos->fs, end, scratch_pool));
  SVN_ERR(svn_fs_check_path(&kind, root, path, scratch_pool));
  if (kind != svn_node_file)
    return svn_error_createf(SVN_ERR_FS_NOT_FILE,
                             NULL, _("'%s' is not a file in revision %ld"),
                             path, end);

  /* Open a history object. */
  SVN_ERR(svn_fs_node_history2(&history, root, path, scratch_pool, iterpool));
  while (1)
    {
      struct path_revision *path_rev;
      svn_revnum_t tmp_revnum;
      const char *tmp_path;

      svn_pool_clear(iterpool);

      /* Fetch the history object to walk through. */
      SVN_ERR(svn_fs_history_prev2(&history, history, TRUE, iterpool,
                                   iterpool));
      if (!history)
        break;
      SVN_ERR(svn_fs_history_location(&tmp_path, &tmp_revnum,
                                      history, iterpool));

      /* Check authorization. */
      if (authz_read_func)
        {
          svn_boolean_t readable;
          svn_fs_root_t *tmp_root;

          SVN_ERR(svn_fs_revision_root(&tmp_root, repos->fs, tmp_revnum,
                                       iterpool));
          SVN_ERR(authz_read_func(&readable, tmp_root, tmp_path,
                                  authz_read_baton, iterpool));
          if (! readable)
            break;
        }

      /* We didn't break, so we must really want this path-rev. */
      path_rev = apr_palloc(iterpool, sizeof(*path_rev));
      path_rev->path = tmp_path;
      path_rev->revnum = tmp_revnum;
      path_rev->merged = FALSE;

      SVN_ERR(send_path_revision(path_rev, repos, &sb,
                                 handler, handler_baton));

      if (path_rev->revnum <= start)
        break;

      /* Swap pools. */
      {
        apr_pool_t *tmp_pool = iterpool;
        iterpool = last_pool;
        last_pool = tmp_pool;
      }
    }

  svn_pool_destroy(iterpool);
  svn_pool_destroy(last_pool);
  svn_pool_destroy(sb.last_pool);
  svn_pool_destroy(sb.iterpool);

  return SVN_NO_ERROR;

}