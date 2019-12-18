#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_revision_access_level_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change_iterator_t ;
struct TYPE_7__ {char* data; } ;
struct TYPE_8__ {scalar_t__ node_kind; scalar_t__ change_kind; char* copyfrom_path; int /*<<< orphan*/  copyfrom_rev; void* copyfrom_known; TYPE_1__ path; } ;
typedef  TYPE_2__ svn_fs_path_change3_t ;
typedef  int /*<<< orphan*/  svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  path_change_receiver_baton; int /*<<< orphan*/  (* path_change_receiver ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  authz_read_baton; int /*<<< orphan*/  (* authz_read_func ) (void**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ log_callbacks_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  stub1 (void**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_copied_from (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_history_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_history_prev2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_history2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_path_change_add ; 
 scalar_t__ svn_fs_path_change_delete ; 
 int /*<<< orphan*/  svn_fs_path_change_get (TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_path_change_replace ; 
 int /*<<< orphan*/  svn_fs_paths_changed3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_revision_access_full ; 
 int /*<<< orphan*/  svn_repos_revision_access_none ; 
 int /*<<< orphan*/  svn_repos_revision_access_partial ; 

__attribute__((used)) static svn_error_t *
detect_changed(svn_repos_revision_access_level_t *access_level,
               svn_fs_root_t *root,
               svn_fs_t *fs,
               const log_callbacks_t *callbacks,
               apr_pool_t *scratch_pool)
{
  svn_fs_path_change_iterator_t *iterator;
  svn_fs_path_change3_t *change;
  apr_pool_t *iterpool;
  svn_boolean_t found_readable = FALSE;
  svn_boolean_t found_unreadable = FALSE;

  /* Retrieve the first change in the list. */
  SVN_ERR(svn_fs_paths_changed3(&iterator, root, scratch_pool, scratch_pool));
  SVN_ERR(svn_fs_path_change_get(&change, iterator));

  if (!change)
    {
      /* No paths changed in this revision?  Uh, sure, I guess the
         revision is readable, then.  */
      *access_level = svn_repos_revision_access_full;
      return SVN_NO_ERROR;
    }

  iterpool = svn_pool_create(scratch_pool);
  while (change)
    {
      /* NOTE:  Much of this loop is going to look quite similar to
         svn_repos_check_revision_access(), but we have to do more things
         here, so we'll live with the duplication. */
      const char *path = change->path.data;
      svn_pool_clear(iterpool);

      /* Skip path if unreadable. */
      if (callbacks->authz_read_func)
        {
          svn_boolean_t readable;
          SVN_ERR(callbacks->authz_read_func(&readable, root, path,
                                             callbacks->authz_read_baton,
                                             iterpool));
          if (! readable)
            {
              found_unreadable = TRUE;
              SVN_ERR(svn_fs_path_change_get(&change, iterator));
              continue;
            }
        }

      /* At least one changed-path was readable. */
      found_readable = TRUE;

      /* Pre-1.6 revision files don't store the change path kind, so fetch
         it manually. */
      if (change->node_kind == svn_node_unknown)
        {
          svn_fs_root_t *check_root = root;
          const char *check_path = path;

          /* Deleted items don't exist so check earlier revision.  We
             know the parent must exist and could be a copy */
          if (change->change_kind == svn_fs_path_change_delete)
            {
              svn_fs_history_t *history;
              svn_revnum_t prev_rev;
              const char *parent_path, *name;

              svn_fspath__split(&parent_path, &name, path, iterpool);

              SVN_ERR(svn_fs_node_history2(&history, root, parent_path,
                                           iterpool, iterpool));

              /* Two calls because the first call returns the original
                 revision as the deleted child means it is 'interesting' */
              SVN_ERR(svn_fs_history_prev2(&history, history, TRUE, iterpool,
                                           iterpool));
              SVN_ERR(svn_fs_history_prev2(&history, history, TRUE, iterpool,
                                           iterpool));

              SVN_ERR(svn_fs_history_location(&parent_path, &prev_rev,
                                              history, iterpool));
              SVN_ERR(svn_fs_revision_root(&check_root, fs, prev_rev,
                                           iterpool));
              check_path = svn_fspath__join(parent_path, name, iterpool);
            }

          SVN_ERR(svn_fs_check_path(&change->node_kind, check_root, check_path,
                                    iterpool));
        }

      if (   (change->change_kind == svn_fs_path_change_add)
          || (change->change_kind == svn_fs_path_change_replace))
        {
          const char *copyfrom_path = change->copyfrom_path;
          svn_revnum_t copyfrom_rev = change->copyfrom_rev;

          /* the following is a potentially expensive operation since on FSFS
             we will follow the DAG from ROOT to PATH and that requires
             actually reading the directories along the way. */
          if (!change->copyfrom_known)
            {
              SVN_ERR(svn_fs_copied_from(&copyfrom_rev, &copyfrom_path,
                                        root, path, iterpool));
              change->copyfrom_known = TRUE;
            }

          if (copyfrom_path && SVN_IS_VALID_REVNUM(copyfrom_rev))
            {
              svn_boolean_t readable = TRUE;

              if (callbacks->authz_read_func)
                {
                  svn_fs_root_t *copyfrom_root;

                  SVN_ERR(svn_fs_revision_root(&copyfrom_root, fs,
                                               copyfrom_rev, iterpool));
                  SVN_ERR(callbacks->authz_read_func(&readable,
                                                     copyfrom_root,
                                                     copyfrom_path,
                                                     callbacks->authz_read_baton,
                                                     iterpool));
                  if (! readable)
                    found_unreadable = TRUE;
                }

              if (readable)
                {
                  change->copyfrom_path = copyfrom_path;
                  change->copyfrom_rev = copyfrom_rev;
                }
            }
        }

      if (callbacks->path_change_receiver)
        SVN_ERR(callbacks->path_change_receiver(
                                     callbacks->path_change_receiver_baton,
                                     change,
                                     iterpool));

      /* Next changed path. */
      SVN_ERR(svn_fs_path_change_get(&change, iterator));
    }

  svn_pool_destroy(iterpool);

  if (! found_readable)
    {
      /* Every changed-path was unreadable. */
      *access_level = svn_repos_revision_access_none;
    }
  else if (found_unreadable)
    {
      /* At least one changed-path was unreadable. */
      *access_level = svn_repos_revision_access_partial;
    }
  else
    {
      /* Every changed-path was readable. */
      *access_level = svn_repos_revision_access_full;
    }

  return SVN_NO_ERROR;
}