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
struct TYPE_9__ {scalar_t__ change_kind; void* prop_mod; void* text_mod; int /*<<< orphan*/  node_rev_id; } ;
typedef  TYPE_1__ svn_fs_path_change2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {char const* path; scalar_t__ kind; void* prop_mod; void* text_mod; int /*<<< orphan*/  noderev_id; } ;
typedef  TYPE_2__ change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* change_to_fs_change (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__id_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  svn_fs_path_change_add 132 
#define  svn_fs_path_change_delete 131 
#define  svn_fs_path_change_modify 130 
#define  svn_fs_path_change_replace 129 
#define  svn_fs_path_change_reset 128 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
fold_change(apr_hash_t *changes,
            apr_hash_t *deletions,
            const change_t *change)
{
  apr_pool_t *pool = apr_hash_pool_get(changes);
  svn_fs_path_change2_t *old_change, *new_change;
  const char *path;

  if ((old_change = svn_hash_gets(changes, change->path)))
    {
      /* This path already exists in the hash, so we have to merge
         this change into the already existing one. */

      /* Since the path already exists in the hash, we don't have to
         dup the allocation for the path itself. */
      path = change->path;

      /* Sanity check:  only allow NULL node revision ID in the
         `reset' case. */
      if ((! change->noderev_id) && (change->kind != svn_fs_path_change_reset))
        return svn_error_create
          (SVN_ERR_FS_CORRUPT, NULL,
           _("Missing required node revision ID"));

      /* Sanity check:  we should be talking about the same node
         revision ID as our last change except where the last change
         was a deletion. */
      if (change->noderev_id
          && (! svn_fs_base__id_eq(old_change->node_rev_id,
                                   change->noderev_id))
          && (old_change->change_kind != svn_fs_path_change_delete))
        return svn_error_create
          (SVN_ERR_FS_CORRUPT, NULL,
           _("Invalid change ordering: new node revision ID without delete"));

      /* Sanity check: an add, replacement, or reset must be the first
         thing to follow a deletion. */
      if ((old_change->change_kind == svn_fs_path_change_delete)
          && (! ((change->kind == svn_fs_path_change_replace)
                 || (change->kind == svn_fs_path_change_reset)
                 || (change->kind == svn_fs_path_change_add))))
        return svn_error_create
          (SVN_ERR_FS_CORRUPT, NULL,
           _("Invalid change ordering: non-add change on deleted path"));

      /* Sanity check: an add can't follow anything except
         a delete or reset.  */
      if ((change->kind == svn_fs_path_change_add)
          && (old_change->change_kind != svn_fs_path_change_delete)
          && (old_change->change_kind != svn_fs_path_change_reset))
        return svn_error_create
          (SVN_ERR_FS_CORRUPT, NULL,
           _("Invalid change ordering: add change on preexisting path"));

      /* Now, merge that change in. */
      switch (change->kind)
        {
        case svn_fs_path_change_reset:
          /* A reset here will simply remove the path change from the
             hash. */
          new_change = NULL;
          break;

        case svn_fs_path_change_delete:
          if (old_change->change_kind == svn_fs_path_change_add)
            {
              /* If the path was introduced in this transaction via an
                 add, and we are deleting it, just remove the path
                 altogether. */
              new_change = NULL;
            }
          else if (old_change->change_kind == svn_fs_path_change_replace)
            {
              /* A deleting a 'replace' restore the original deletion. */
              new_change = svn_hash_gets(deletions, path);
              SVN_ERR_ASSERT(new_change);
            }
          else
            {
              /* A deletion overrules all previous changes. */
              new_change = old_change;
              new_change->change_kind = svn_fs_path_change_delete;
              new_change->text_mod = change->text_mod;
              new_change->prop_mod = change->prop_mod;
            }
          break;

        case svn_fs_path_change_add:
        case svn_fs_path_change_replace:
          /* An add at this point must be following a previous delete,
             so treat it just like a replace. */

          new_change = change_to_fs_change(change, pool);
          new_change->change_kind = svn_fs_path_change_replace;

          /* Remember the original deletion.
           * Make sure to allocate the hash key in a durable pool. */
          svn_hash_sets(deletions,
                        apr_pstrdup(apr_hash_pool_get(deletions), path),
                        old_change);
          break;

        case svn_fs_path_change_modify:
        default:
          new_change = old_change;
          if (change->text_mod)
            new_change->text_mod = TRUE;
          if (change->prop_mod)
            new_change->prop_mod = TRUE;
          break;
        }
    }
  else
    {
      /* This change is new to the hash, so make a new public change
         structure from the internal one (in the hash's pool), and dup
         the path into the hash's pool, too. */
      new_change = change_to_fs_change(change, pool);
      path = apr_pstrdup(pool, change->path);
    }

  /* Add (or update) this path. */
  svn_hash_sets(changes, path, new_change);

  return SVN_NO_ERROR;
}