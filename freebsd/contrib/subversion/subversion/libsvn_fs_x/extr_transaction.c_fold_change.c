#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
struct TYPE_10__ {scalar_t__ change_kind; TYPE_1__ path; int /*<<< orphan*/  mergeinfo_mod; void* prop_mod; void* text_mod; } ;
typedef  TYPE_2__ svn_fs_x__change_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* apr_hash_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* path_change_dup (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  svn_fs_path_change_add 131 
#define  svn_fs_path_change_delete 130 
#define  svn_fs_path_change_modify 129 
#define  svn_fs_path_change_replace 128 
 int /*<<< orphan*/  svn_tristate_true ; 

__attribute__((used)) static svn_error_t *
fold_change(apr_hash_t *changed_paths,
            apr_hash_t *deletions,
            const svn_fs_x__change_t *change)
{
  apr_pool_t *pool = apr_hash_pool_get(changed_paths);
  svn_fs_x__change_t *old_change, *new_change;
  const svn_string_t *path = &change->path;

  if ((old_change = apr_hash_get(changed_paths, path->data, path->len)))
    {
      /* This path already exists in the hash, so we have to merge
         this change into the already existing one. */

      /* Sanity check: an add, replacement, or reset must be the first
         thing to follow a deletion. */
      if ((old_change->change_kind == svn_fs_path_change_delete)
          && (! ((change->change_kind == svn_fs_path_change_replace)
                 || (change->change_kind == svn_fs_path_change_add))))
        return svn_error_create
          (SVN_ERR_FS_CORRUPT, NULL,
           _("Invalid change ordering: non-add change on deleted path"));

      /* Sanity check: an add can't follow anything except
         a delete or reset.  */
      if ((change->change_kind == svn_fs_path_change_add)
          && (old_change->change_kind != svn_fs_path_change_delete))
        return svn_error_create
          (SVN_ERR_FS_CORRUPT, NULL,
           _("Invalid change ordering: add change on preexisting path"));

      /* Now, merge that change in. */
      switch (change->change_kind)
        {
        case svn_fs_path_change_delete:
          if (old_change->change_kind == svn_fs_path_change_add)
            {
              /* If the path was introduced in this transaction via an
                 add, and we are deleting it, just remove the path
                 altogether.  (The caller will delete any child paths.) */
              apr_hash_set(changed_paths, path->data, path->len, NULL);
            }
          else if (old_change->change_kind == svn_fs_path_change_replace)
            {
              /* A deleting a 'replace' restore the original deletion. */
              new_change = apr_hash_get(deletions, path->data, path->len);
              SVN_ERR_ASSERT(new_change);
              apr_hash_set(changed_paths, path->data, path->len, new_change);
            }
          else
            {
              /* A deletion overrules a previous change (modify). */
              new_change = path_change_dup(change, pool);
              apr_hash_set(changed_paths, path->data, path->len, new_change);
            }
          break;

        case svn_fs_path_change_add:
        case svn_fs_path_change_replace:
          /* An add at this point must be following a previous delete,
             so treat it just like a replace.  Remember the original
             deletion such that we are able to delete this path again
             (the replacement may have changed node kind and id). */
          new_change = path_change_dup(change, pool);
          new_change->change_kind = svn_fs_path_change_replace;

          apr_hash_set(changed_paths, path->data, path->len, new_change);

          /* Remember the original change.
           * Make sure to allocate the hash key in a durable pool. */
          apr_hash_set(deletions,
                       apr_pstrmemdup(apr_hash_pool_get(deletions),
                                      path->data, path->len),
                       path->len, old_change);
          break;

        case svn_fs_path_change_modify:
        default:
          /* If the new change modifies some attribute of the node, set
             the corresponding flag, whether it already was set or not.
             Note: We do not reset a flag to FALSE if a change is undone. */
          if (change->text_mod)
            old_change->text_mod = TRUE;
          if (change->prop_mod)
            old_change->prop_mod = TRUE;
          if (change->mergeinfo_mod == svn_tristate_true)
            old_change->mergeinfo_mod = svn_tristate_true;
          break;
        }
    }
  else
    {
      /* Add this path.  The API makes no guarantees that this (new) key
         will not be retained.  Thus, we copy the key into the target pool
         to ensure a proper lifetime.  */
      new_change = path_change_dup(change, pool);
      apr_hash_set(changed_paths, new_change->path.data,
                   new_change->path.len, new_change);
    }

  return SVN_NO_ERROR;
}