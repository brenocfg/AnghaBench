#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int len; char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_16__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  txn; scalar_t__ is_txn_root; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_17__ {int /*<<< orphan*/  copy_src_path; void* copy_inherit; int /*<<< orphan*/ * node; } ;
typedef  TYPE_3__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  void* copy_id_inherit_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  SVN_FS__ERR_NOT_DIRECTORY (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * SVN_FS__NOT_FOUND (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* copy_id_inherit_self ; 
 int /*<<< orphan*/  dag_node_cache_get (int /*<<< orphan*/ **,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dag_node_cache_set (TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_copy_inheritance (void**,char const**,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* make_parent_path (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int open_path_allow_null ; 
 int open_path_last_optional ; 
 int open_path_node_only ; 
 int open_path_uncached ; 
 int /*<<< orphan*/  root_node (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__is_canonical_abspath (char const*) ; 
 char* svn_fs__next_entry_name (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__dag_node_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_match_last_node (int /*<<< orphan*/ **,TYPE_2__*,char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_path(parent_path_t **parent_path_p,
          svn_fs_root_t *root,
          const char *path,
          int flags,
          svn_boolean_t is_txn_path,
          apr_pool_t *pool)
{
  svn_fs_t *fs = root->fs;
  dag_node_t *here = NULL; /* The directory we're currently looking at.  */
  parent_path_t *parent_path; /* The path from HERE up to the root. */
  const char *rest = NULL; /* The portion of PATH we haven't traversed yet. */
  apr_pool_t *iterpool = svn_pool_create(pool);

  /* path to the currently processed entry without trailing '/'.
     We will reuse this across iterations by simply putting a NUL terminator
     at the respective position and replacing that with a '/' in the next
     iteration.  This is correct as we assert() PATH to be canonical. */
  svn_stringbuf_t *path_so_far = svn_stringbuf_create(path, pool);
  apr_size_t path_len = path_so_far->len;

  /* Callers often traverse the DAG in some path-based order or along the
     history segments.  That allows us to try a few guesses about where to
     find the next item.  This is only useful if the caller didn't request
     the full parent chain. */
  assert(svn_fs__is_canonical_abspath(path));
  path_so_far->len = 0; /* "" */
  if (flags & open_path_node_only)
    {
      const char *directory;

      /* First attempt: Assume that we access the DAG for the same path as
         in the last lookup but for a different revision that happens to be
         the last revision that touched the respective node.  This is a
         common pattern when e.g. checking out over ra_serf.  Note that this
         will only work for committed data as the revision info for nodes in
         txns is bogus.

         This shortcut is quick and will exit this function upon success.
         So, try it first. */
      if (!root->is_txn_root)
        {
          dag_node_t *node;
          SVN_ERR(try_match_last_node(&node, root, path, path_len, iterpool));

          /* Did the shortcut work? */
          if (node)
            {
              /* Construct and return the result. */
              svn_pool_destroy(iterpool);

              parent_path = make_parent_path(node, 0, 0, pool);
              parent_path->copy_inherit = copy_id_inherit_self;
              *parent_path_p = parent_path;

              return SVN_NO_ERROR;
            }
        }

      /* Second attempt: Try starting the lookup immediately at the parent
         node.  We will often have recently accessed either a sibling or
         said parent DIRECTORY itself for the same revision. */
      directory = svn_dirent_dirname(path, pool);
      if (directory[1] != 0) /* root nodes are covered anyway */
        {
          SVN_ERR(dag_node_cache_get(&here, root, directory, pool));

          /* Did the shortcut work? */
          if (here)
            {
              apr_size_t dirname_len = strlen(directory);
              path_so_far->len = dirname_len;
              rest = path + dirname_len + 1;
            }
        }
    }

  /* did the shortcut work? */
  if (!here)
    {
      /* Make a parent_path item for the root node, using its own current
         copy id.  */
      SVN_ERR(root_node(&here, root, pool));
      rest = path + 1; /* skip the leading '/', it saves in iteration */
    }

  path_so_far->data[path_so_far->len] = '\0';
  parent_path = make_parent_path(here, 0, 0, pool);
  parent_path->copy_inherit = copy_id_inherit_self;

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

      svn_pool_clear(iterpool);

      /* Parse out the next entry from the path.  */
      entry = svn_fs__next_entry_name(&next, rest, pool);

      /* Update the path traversed thus far. */
      path_so_far->data[path_so_far->len] = '/';
      path_so_far->len += strlen(entry) + 1;
      path_so_far->data[path_so_far->len] = '\0';

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
          dag_node_t *cached_node = NULL;

          /* If we found a directory entry, follow it.  First, we
             check our node cache, and, failing that, we hit the DAG
             layer.  Don't bother to contact the cache for the last
             element if we already know the lookup to fail for the
             complete path. */
          if (next || !(flags & open_path_uncached))
            SVN_ERR(dag_node_cache_get(&cached_node, root, path_so_far->data,
                                       pool));
          if (cached_node)
            child = cached_node;
          else
            SVN_ERR(svn_fs_fs__dag_open(&child, here, entry, pool, iterpool));

          /* "file not found" requires special handling.  */
          if (child == NULL)
            {
              /* If this was the last path component, and the caller
                 said it was optional, then don't return an error;
                 just put a NULL node pointer in the path.  */

              if ((flags & open_path_last_optional)
                  && (! next || *next == '\0'))
                {
                  parent_path = make_parent_path(NULL, entry, parent_path,
                                                 pool);
                  break;
                }
              else if (flags & open_path_allow_null)
                {
                  parent_path = NULL;
                  break;
                }
              else
                {
                  /* Build a better error message than svn_fs_fs__dag_open
                     can provide, giving the root and full path name.  */
                  return SVN_FS__NOT_FOUND(root, path);
                }
            }

          if (flags & open_path_node_only)
            {
              /* Shortcut: the caller only wants the final DAG node. */
              parent_path->node = child;
            }
          else
            {
              /* Now, make a parent_path item for CHILD. */
              parent_path = make_parent_path(child, entry, parent_path, pool);
              if (is_txn_path)
                {
                  SVN_ERR(get_copy_inheritance(&inherit, &copy_path, fs,
                                               parent_path, iterpool));
                  parent_path->copy_inherit = inherit;
                  parent_path->copy_src_path = apr_pstrdup(pool, copy_path);
                }
            }

          /* Cache the node we found (if it wasn't already cached). */
          if (! cached_node)
            SVN_ERR(dag_node_cache_set(root, path_so_far->data, child,
                                       iterpool));
        }

      /* Are we finished traversing the path?  */
      if (! next)
        break;

      /* The path isn't finished yet; we'd better be in a directory.  */
      if (svn_fs_fs__dag_node_kind(child) != svn_node_dir)
        {
          const char *msg;

          /* Since this is not a directory and we are looking for some
             sub-path, that sub-path will not exist.  That will be o.k.,
             if we are just here to check for the path's existence. */
          if (flags & open_path_allow_null)
            {
              parent_path = NULL;
              break;
            }

          /* It's really a problem ... */
          msg = root->is_txn_root
              ? apr_psprintf(iterpool,
                             _("Failure opening '%s' in transaction '%s'"),
                             path, root->txn)
              : apr_psprintf(iterpool,
                             _("Failure opening '%s' in revision %ld"),
                             path, root->rev);
          SVN_ERR_W(SVN_FS__ERR_NOT_DIRECTORY(fs, path_so_far->data), msg);
        }

      rest = next;
      here = child;
    }

  svn_pool_destroy(iterpool);
  *parent_path_p = parent_path;
  return SVN_NO_ERROR;
}