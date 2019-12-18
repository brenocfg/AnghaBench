#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_21__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct TYPE_23__ {int /*<<< orphan*/  copy_src_path; int /*<<< orphan*/  copy_inherit; } ;
typedef  TYPE_3__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  copy_id_inherit_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS__ERR_NOT_DIRECTORY (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* SVN_FS__NOT_FOUND (TYPE_1__*,char const*) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  copy_id_inherit_self ; 
 int /*<<< orphan*/ * dag_node_cache_get (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dag_node_cache_set (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* get_copy_inheritance (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* make_parent_path (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int open_path_last_optional ; 
 TYPE_2__* root_node (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 char* svn_fs__next_entry_name (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_base__dag_node_kind (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_fs_base__dag_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 

__attribute__((used)) static svn_error_t *
open_path(parent_path_t **parent_path_p,
          svn_fs_root_t *root,
          const char *path,
          int flags,
          const char *txn_id,
          trail_t *trail,
          apr_pool_t *pool)
{
  svn_fs_t *fs = root->fs;
  dag_node_t *here; /* The directory we're currently looking at.  */
  parent_path_t *parent_path; /* The path from HERE up to the root.  */
  const char *rest; /* The portion of PATH we haven't traversed yet.  */
  const char *canon_path = svn_fs__canonicalize_abspath(path, pool);
  const char *path_so_far = "/";

  /* Make a parent_path item for the root node, using its own current
     copy id.  */
  SVN_ERR(root_node(&here, root, trail, pool));
  parent_path = make_parent_path(here, 0, 0, pool);
  parent_path->copy_inherit = copy_id_inherit_self;

  rest = canon_path + 1; /* skip the leading '/', it saves in iteration */

  /* Whenever we are at the top of this loop:
     - HERE is our current directory,
     - ID is the node revision ID of HERE,
     - REST is the path we're going to find in HERE, and
     - PARENT_PATH includes HERE and all its parents.  */
  for (;;)
    {
      const char *next;
      char *entry;
      dag_node_t *child;

      /* Parse out the next entry from the path.  */
      entry = svn_fs__next_entry_name(&next, rest, pool);

      /* Calculate the path traversed thus far. */
      path_so_far = svn_fspath__join(path_so_far, entry, pool);

      if (*entry == '\0')
        {
          /* Given the behavior of svn_fs__next_entry_name(), this
             happens when the path either starts or ends with a slash.
             In either case, we stay put: the current directory stays
             the same, and we add nothing to the parent path. */
          child = here;
        }
      else
        {
          copy_id_inherit_t inherit;
          const char *copy_path = NULL;
          svn_error_t *err = SVN_NO_ERROR;
          dag_node_t *cached_node;

          /* If we found a directory entry, follow it.  First, we
             check our node cache, and, failing that, we hit the DAG
             layer. */
          cached_node = dag_node_cache_get(root, path_so_far, pool);
          if (cached_node)
            child = cached_node;
          else
            err = svn_fs_base__dag_open(&child, here, entry, trail, pool);

          /* "file not found" requires special handling.  */
          if (err && err->apr_err == SVN_ERR_FS_NOT_FOUND)
            {
              /* If this was the last path component, and the caller
                 said it was optional, then don't return an error;
                 just put a NULL node pointer in the path.  */

              svn_error_clear(err);

              if ((flags & open_path_last_optional)
                  && (! next || *next == '\0'))
                {
                  parent_path = make_parent_path(NULL, entry, parent_path,
                                                 pool);
                  break;
                }
              else
                {
                  /* Build a better error message than svn_fs_base__dag_open
                     can provide, giving the root and full path name.  */
                  return SVN_FS__NOT_FOUND(root, path);
                }
            }

          /* Other errors we return normally.  */
          SVN_ERR(err);

          /* Now, make a parent_path item for CHILD. */
          parent_path = make_parent_path(child, entry, parent_path, pool);
          if (txn_id)
            {
              SVN_ERR(get_copy_inheritance(&inherit, &copy_path,
                                           fs, parent_path, txn_id,
                                           trail, pool));
              parent_path->copy_inherit = inherit;
              parent_path->copy_src_path = apr_pstrdup(pool, copy_path);
            }

          /* Cache the node we found (if it wasn't already cached). */
          if (! cached_node)
            dag_node_cache_set(root, path_so_far, child);
        }

      /* Are we finished traversing the path?  */
      if (! next)
        break;

      /* The path isn't finished yet; we'd better be in a directory.  */
      if (svn_fs_base__dag_node_kind(child) != svn_node_dir)
        SVN_ERR_W(SVN_FS__ERR_NOT_DIRECTORY(fs, path_so_far),
                  apr_psprintf(pool, _("Failure opening '%s'"), path));

      rest = next;
      here = child;
    }

  *parent_path_p = parent_path;
  return SVN_NO_ERROR;
}