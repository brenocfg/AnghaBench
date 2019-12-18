#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* repos_root_url; int node_status; char const* changelist; char* moved_from_abspath; scalar_t__ revision; char* repos_relpath; int const text_status; int const prop_status; int /*<<< orphan*/  kind; scalar_t__ copied; int /*<<< orphan*/  lock; scalar_t__ switched; scalar_t__ file_external; scalar_t__ conflicted; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client__committables_t ;
typedef  int svn_boolean_t ;
struct harvest_baton {char const* commit_relpath; int just_locked; int /*<<< orphan*/  check_url_baton; int /*<<< orphan*/  (* check_url_func ) (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * result_pool; int /*<<< orphan*/ * skip_below_abspath; int /*<<< orphan*/ * danglers; int /*<<< orphan*/ * changelists; scalar_t__ lock_tokens; int /*<<< orphan*/  root_abspath; int /*<<< orphan*/ * wc_ctx; void* notify_baton; int /*<<< orphan*/  (* notify_func ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * committables; } ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int apr_byte_t ;

/* Variables and functions */
 int FALSE ; 
 int SVN_CLIENT_COMMIT_ITEM_ADD ; 
 int SVN_CLIENT_COMMIT_ITEM_DELETE ; 
 int SVN_CLIENT_COMMIT_ITEM_IS_COPY ; 
 int SVN_CLIENT_COMMIT_ITEM_LOCK_TOKEN ; 
 int SVN_CLIENT_COMMIT_ITEM_MOVED_HERE ; 
 int SVN_CLIENT_COMMIT_ITEM_PROP_MODS ; 
 int SVN_CLIENT_COMMIT_ITEM_TEXT_MODS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNEXPECTED_KIND ; 
 int /*<<< orphan*/  SVN_ERR_WC_FOUND_CONFLICT ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_committable (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,char const*,scalar_t__,char const*,scalar_t__,char const*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (scalar_t__,void const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  harvest_not_present_for_copy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ look_up_committable (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_ancestor (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_base (int /*<<< orphan*/ *,scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_commit_status (int*,int*,int*,int*,scalar_t__*,scalar_t__*,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_lock_tokens_recursive (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_origin (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_is_added (int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_failed_conflict ; 
 int /*<<< orphan*/  svn_wc_notify_failed_missing ; 
 int /*<<< orphan*/  svn_wc_notify_failed_obstruction ; 
#define  svn_wc_status_external 132 
#define  svn_wc_status_ignored 131 
 int svn_wc_status_missing ; 
#define  svn_wc_status_none 130 
#define  svn_wc_status_normal 129 
 int svn_wc_status_obstructed ; 
#define  svn_wc_status_unversioned 128 

__attribute__((used)) static svn_error_t *
harvest_status_callback(void *status_baton,
                        const char *local_abspath,
                        const svn_wc_status3_t *status,
                        apr_pool_t *scratch_pool)
{
  apr_byte_t state_flags = 0;
  svn_revnum_t node_rev;
  const char *cf_relpath = NULL;
  svn_revnum_t cf_rev = SVN_INVALID_REVNUM;
  svn_boolean_t matches_changelists;
  svn_boolean_t is_added;
  svn_boolean_t is_deleted;
  svn_boolean_t is_replaced;
  svn_boolean_t is_op_root;
  svn_revnum_t original_rev;
  const char *original_relpath;
  svn_boolean_t copy_mode;

  struct harvest_baton *baton = status_baton;
  svn_boolean_t is_harvest_root =
                (strcmp(baton->root_abspath, local_abspath) == 0);
  svn_client__committables_t *committables = baton->committables;
  const char *repos_root_url = status->repos_root_url;
  const char *commit_relpath = NULL;
  svn_boolean_t copy_mode_root = (baton->commit_relpath && is_harvest_root);
  svn_boolean_t just_locked = baton->just_locked;
  apr_hash_t *changelists = baton->changelists;
  svn_wc_notify_func2_t notify_func = baton->notify_func;
  void *notify_baton = baton->notify_baton;
  svn_wc_context_t *wc_ctx = baton->wc_ctx;
  apr_pool_t *result_pool = baton->result_pool;
  const char *moved_from_abspath = NULL;

  if (baton->commit_relpath)
    commit_relpath = svn_relpath_join(
                        baton->commit_relpath,
                        svn_dirent_skip_ancestor(baton->root_abspath,
                                                 local_abspath),
                        scratch_pool);

  copy_mode = (commit_relpath != NULL);

  if (baton->skip_below_abspath
      && svn_dirent_is_ancestor(baton->skip_below_abspath, local_abspath))
    {
      return SVN_NO_ERROR;
    }
  else
    baton->skip_below_abspath = NULL; /* We have left the skip tree */

  /* Return early for nodes that don't have a committable status */
  switch (status->node_status)
    {
      case svn_wc_status_unversioned:
      case svn_wc_status_ignored:
      case svn_wc_status_external:
      case svn_wc_status_none:
        /* Unversioned nodes aren't committable, but are reported by the status
           walker.
           But if the unversioned node is the root of the walk, we have a user
           error */
        if (is_harvest_root)
          return svn_error_createf(
                       SVN_ERR_ILLEGAL_TARGET, NULL,
                       _("'%s' is not under version control"),
                       svn_dirent_local_style(local_abspath, scratch_pool));
        return SVN_NO_ERROR;
      case svn_wc_status_normal:
        /* Status normal nodes aren't modified, so we don't have to commit them
           when we perform a normal commit. But if a node is conflicted we want
           to stop the commit and if we are collecting lock tokens we want to
           look further anyway.

           When in copy mode we need to compare the revision of the node against
           the parent node to copy mixed-revision base nodes properly */
        if (!copy_mode && !status->conflicted
            && !(just_locked && status->lock))
          return SVN_NO_ERROR;
        break;
      default:
        /* Fall through */
        break;
    }

  /* Early out if the item is already marked as committable. */
  if (look_up_committable(committables, local_abspath, scratch_pool))
    return SVN_NO_ERROR;

  SVN_ERR_ASSERT((copy_mode && commit_relpath)
                 || (! copy_mode && ! commit_relpath));
  SVN_ERR_ASSERT((copy_mode_root && copy_mode) || ! copy_mode_root);

  /* Save the result for reuse. */
  matches_changelists = ((changelists == NULL)
                         || (status->changelist != NULL
                             && svn_hash_gets(changelists, status->changelist)
                                != NULL));

  /* Early exit. */
  if (status->kind != svn_node_dir && ! matches_changelists)
    {
      return SVN_NO_ERROR;
    }

  /* If NODE is in our changelist, then examine it for conflicts. We
     need to bail out if any conflicts exist.
     The status walker checked for conflict marker removal. */
  if (status->conflicted && matches_changelists)
    {
      if (notify_func != NULL)
        {
          notify_func(notify_baton,
                      svn_wc_create_notify(local_abspath,
                                           svn_wc_notify_failed_conflict,
                                           scratch_pool),
                      scratch_pool);
        }

      return svn_error_createf(
            SVN_ERR_WC_FOUND_CONFLICT, NULL,
            _("Aborting commit: '%s' remains in conflict"),
            svn_dirent_local_style(local_abspath, scratch_pool));
    }
  else if (status->node_status == svn_wc_status_obstructed)
    {
      /* A node's type has changed before attempting to commit.
         This also catches symlink vs non symlink changes */

      if (notify_func != NULL)
        {
          notify_func(notify_baton,
                      svn_wc_create_notify(local_abspath,
                                           svn_wc_notify_failed_obstruction,
                                           scratch_pool),
                      scratch_pool);
        }

      return svn_error_createf(
                    SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                    _("Node '%s' has unexpectedly changed kind"),
                    svn_dirent_local_style(local_abspath, scratch_pool));
    }

  if (status->conflicted && status->kind == svn_node_unknown)
    return SVN_NO_ERROR; /* Ignore delete-delete conflict */

  /* Return error on unknown path kinds.  We check both the entry and
     the node itself, since a path might have changed kind since its
     entry was written. */
  SVN_ERR(svn_wc__node_get_commit_status(&is_added, &is_deleted,
                                         &is_replaced,
                                         &is_op_root,
                                         &node_rev,
                                         &original_rev, &original_relpath,
                                         wc_ctx, local_abspath,
                                         scratch_pool, scratch_pool));

  /* Hande file externals only when passed as explicit target. Note that
   * svn_client_commit6() passes all committable externals in as explicit
   * targets iff they count. */
  if (status->file_external && !is_harvest_root)
    {
      return SVN_NO_ERROR;
    }

  if (status->node_status == svn_wc_status_missing && matches_changelists)
    {
      /* Added files and directories must exist. See issue #3198. */
      if (is_added && is_op_root)
        {
          if (notify_func != NULL)
            {
              notify_func(notify_baton,
                          svn_wc_create_notify(local_abspath,
                                               svn_wc_notify_failed_missing,
                                               scratch_pool),
                          scratch_pool);
            }
          return svn_error_createf(
             SVN_ERR_WC_PATH_NOT_FOUND, NULL,
             _("'%s' is scheduled for addition, but is missing"),
             svn_dirent_local_style(local_abspath, scratch_pool));
        }

      return SVN_NO_ERROR;
    }

  if (is_deleted && !is_op_root /* && !is_added */)
    return SVN_NO_ERROR; /* Not an operational delete and not an add. */

  /* Check for the deletion case.
     * We delete explicitly deleted nodes (duh!)
     * We delete not-present children of copies
     * We delete nodes that directly replace a node in its ancestor
   */

  if (is_deleted || is_replaced)
    state_flags |= SVN_CLIENT_COMMIT_ITEM_DELETE;

  /* Check for adds and copies */
  if (is_added && is_op_root)
    {
      /* Root of local add or copy */
      state_flags |= SVN_CLIENT_COMMIT_ITEM_ADD;

      if (original_relpath)
        {
          /* Root of copy */
          state_flags |= SVN_CLIENT_COMMIT_ITEM_IS_COPY;
          cf_relpath = original_relpath;
          cf_rev = original_rev;

          if (status->moved_from_abspath && !copy_mode)
            {
              state_flags |= SVN_CLIENT_COMMIT_ITEM_MOVED_HERE;
              moved_from_abspath = status->moved_from_abspath;
            }
        }
    }

  /* Further copies may occur in copy mode. */
  else if (copy_mode
           && !(state_flags & SVN_CLIENT_COMMIT_ITEM_DELETE))
    {
      svn_revnum_t dir_rev = SVN_INVALID_REVNUM;
      const char *dir_repos_relpath = NULL;

      if (!copy_mode_root && !is_added)
        SVN_ERR(svn_wc__node_get_base(NULL, &dir_rev, &dir_repos_relpath, NULL,
                                      NULL, NULL,
                                      wc_ctx, svn_dirent_dirname(local_abspath,
                                                                 scratch_pool),
                                      FALSE /* ignore_enoent */,
                                      scratch_pool, scratch_pool));

      if (copy_mode_root || status->switched || node_rev != dir_rev)
        {
          state_flags |= (SVN_CLIENT_COMMIT_ITEM_ADD
                          | SVN_CLIENT_COMMIT_ITEM_IS_COPY);

          if (status->copied)
            {
              /* Copy from original location */
              cf_rev = original_rev;
              cf_relpath = original_relpath;
            }
          else
            {
              /* Copy BASE location, to represent a mixed-rev or switch copy */
              cf_rev = status->revision;
              cf_relpath = status->repos_relpath;
            }

          if (!copy_mode_root && !is_added && baton->check_url_func
              && dir_repos_relpath)
            {
              svn_node_kind_t me_kind;
              /* Maybe we need to issue an delete (mixed rev/switched) */

              SVN_ERR(baton->check_url_func(
                            baton->check_url_baton, &me_kind,
                            svn_path_url_add_component2(repos_root_url,
                                        svn_relpath_join(dir_repos_relpath,
                                            svn_dirent_basename(local_abspath,
                                                                NULL),
                                            scratch_pool),
                                        scratch_pool),
                                        dir_rev, scratch_pool));
              if (me_kind != svn_node_none)
                state_flags |= SVN_CLIENT_COMMIT_ITEM_DELETE;
            }
        }
    }

  if (!(state_flags & SVN_CLIENT_COMMIT_ITEM_DELETE)
      || (state_flags & SVN_CLIENT_COMMIT_ITEM_ADD))
    {
      svn_boolean_t text_mod = FALSE;
      svn_boolean_t prop_mod = FALSE;

      if (status->kind == svn_node_file)
        {
          /* Check for text modifications on files */
          if ((state_flags & SVN_CLIENT_COMMIT_ITEM_ADD)
              && ! (state_flags & SVN_CLIENT_COMMIT_ITEM_IS_COPY))
            {
              text_mod = TRUE; /* Local added files are always modified */
            }
          else
            text_mod = (status->text_status != svn_wc_status_normal);
        }

      prop_mod = (status->prop_status != svn_wc_status_normal
                  && status->prop_status != svn_wc_status_none);

      /* Set text/prop modification flags accordingly. */
      if (text_mod)
        state_flags |= SVN_CLIENT_COMMIT_ITEM_TEXT_MODS;
      if (prop_mod)
        state_flags |= SVN_CLIENT_COMMIT_ITEM_PROP_MODS;
    }

  /* If the entry has a lock token and it is already a commit candidate,
     or the caller wants unmodified locked items to be treated as
     such, note this fact. */
  if (status->lock && baton->lock_tokens && (state_flags || just_locked))
    {
      state_flags |= SVN_CLIENT_COMMIT_ITEM_LOCK_TOKEN;
    }

  /* Now, if this is something to commit, add it to our list. */
  if (matches_changelists
      && state_flags)
    {
      /* Finally, add the committable item. */
      SVN_ERR(add_committable(committables, local_abspath,
                              status->kind,
                              repos_root_url,
                              copy_mode
                                      ? commit_relpath
                                      : status->repos_relpath,
                              copy_mode
                                      ? SVN_INVALID_REVNUM
                                      : node_rev,
                              cf_relpath,
                              cf_rev,
                              moved_from_abspath,
                              state_flags,
                              baton->lock_tokens, status->lock,
                              result_pool, scratch_pool));
    }

    /* Fetch lock tokens for descendants of deleted BASE nodes. */
  if (matches_changelists
      && (state_flags & SVN_CLIENT_COMMIT_ITEM_DELETE)
      && !copy_mode
      && SVN_IS_VALID_REVNUM(node_rev) /* && BASE-kind = dir */
      && baton->lock_tokens)
    {
      apr_hash_t *local_relpath_tokens;
      apr_hash_index_t *hi;

      SVN_ERR(svn_wc__node_get_lock_tokens_recursive(
                  &local_relpath_tokens, wc_ctx, local_abspath,
                  result_pool, scratch_pool));

      /* Add tokens to existing hash. */
      for (hi = apr_hash_first(scratch_pool, local_relpath_tokens);
           hi;
           hi = apr_hash_next(hi))
        {
          const void *key;
          apr_ssize_t klen;
          void * val;

          apr_hash_this(hi, &key, &klen, &val);

          apr_hash_set(baton->lock_tokens, key, klen, val);
        }
    }

  /* Make sure we check for dangling children on additions

     We perform this operation on the harvest root, and on roots caused by
     changelist filtering.
  */
  if (matches_changelists
      && (is_harvest_root || baton->changelists)
      && state_flags
      && (is_added || (is_deleted && is_op_root && status->copied))
      && baton->danglers)
    {
      /* If a node is added, its parent must exist in the repository at the
         time of committing */
      apr_hash_t *danglers = baton->danglers;
      svn_boolean_t parent_added;
      const char *parent_abspath = svn_dirent_dirname(local_abspath,
                                                      scratch_pool);

      /* First check if parent is already in the list of commits
         (Common case for GUI clients that provide a list of commit targets) */
      if (look_up_committable(committables, parent_abspath, scratch_pool))
        parent_added = FALSE; /* Skip all expensive checks */
      else
        SVN_ERR(svn_wc__node_is_added(&parent_added, wc_ctx, parent_abspath,
                                      scratch_pool));

      if (parent_added)
        {
          const char *copy_root_abspath;
          svn_boolean_t parent_is_copy;

          /* The parent is added, so either it is a copy, or a locally added
           * directory. In either case, we require the op-root of the parent
           * to be part of the commit. See issue #4059. */
          SVN_ERR(svn_wc__node_get_origin(&parent_is_copy, NULL, NULL, NULL,
                                          NULL, NULL, &copy_root_abspath,
                                          wc_ctx, parent_abspath,
                                          FALSE, scratch_pool, scratch_pool));

          if (parent_is_copy)
            parent_abspath = copy_root_abspath;

          if (!svn_hash_gets(danglers, parent_abspath))
            {
              svn_hash_sets(danglers, apr_pstrdup(result_pool, parent_abspath),
                            apr_pstrdup(result_pool, local_abspath));
            }
        }
    }

  if (is_deleted && !is_added)
    {
      /* Skip all descendants */
      if (status->kind == svn_node_dir)
        baton->skip_below_abspath = apr_pstrdup(baton->result_pool,
                                                local_abspath);
      return SVN_NO_ERROR;
    }

  /* Recursively handle each node according to depth, except when the
     node is only being deleted, or is in an added tree (as added trees
     use the normal commit handling). */
  if (copy_mode && !is_added && !is_deleted && status->kind == svn_node_dir)
    {
      SVN_ERR(harvest_not_present_for_copy(wc_ctx, local_abspath, committables,
                                           repos_root_url, commit_relpath,
                                           baton->check_url_func,
                                           baton->check_url_baton,
                                           result_pool, scratch_pool));
    }

  return SVN_NO_ERROR;
}