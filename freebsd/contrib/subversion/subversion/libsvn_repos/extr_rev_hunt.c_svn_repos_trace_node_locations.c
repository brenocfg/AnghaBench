#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  (* svn_repos_authz_func_t ) (scalar_t__*,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  scalar_t__ svn_fs_node_relation_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_6__ {int elt_size; int nelts; scalar_t__ elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 TYPE_1__* apr_array_copy (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  check_ancestry_of_peg_path (scalar_t__*,int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_readability (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  (*) (scalar_t__*,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_relation (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_node_unrelated ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__prev_location (scalar_t__*,char const**,scalar_t__*,int /*<<< orphan*/ *,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sort__array (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sort_compare_revisions ; 

svn_error_t *
svn_repos_trace_node_locations(svn_fs_t *fs,
                               apr_hash_t **locations,
                               const char *fs_path,
                               svn_revnum_t peg_revision,
                               const apr_array_header_t *location_revisions_orig,
                               svn_repos_authz_func_t authz_read_func,
                               void *authz_read_baton,
                               apr_pool_t *pool)
{
  apr_array_header_t *location_revisions;
  svn_revnum_t *revision_ptr, *revision_ptr_end;
  svn_fs_root_t *root;
  const char *path;
  svn_revnum_t revision;
  svn_boolean_t is_ancestor;
  apr_pool_t *lastpool, *currpool;

  SVN_ERR_ASSERT(location_revisions_orig->elt_size == sizeof(svn_revnum_t));

  /* Ensure that FS_PATH is absolute, because our path-math below will
     depend on that being the case.  */
  if (*fs_path != '/')
    fs_path = apr_pstrcat(pool, "/", fs_path, SVN_VA_NULL);

  /* Another sanity check. */
  if (authz_read_func)
    {
      svn_fs_root_t *peg_root;
      SVN_ERR(svn_fs_revision_root(&peg_root, fs, peg_revision, pool));
      SVN_ERR(check_readability(peg_root, fs_path,
                                authz_read_func, authz_read_baton, pool));
    }

  *locations = apr_hash_make(pool);

  /* We flip between two pools in the second loop below. */
  lastpool = svn_pool_create(pool);
  currpool = svn_pool_create(pool);

  /* First - let's sort the array of the revisions from the greatest revision
   * downward, so it will be easier to search on. */
  location_revisions = apr_array_copy(pool, location_revisions_orig);
  svn_sort__array(location_revisions, svn_sort_compare_revisions);

  revision_ptr = (svn_revnum_t *)location_revisions->elts;
  revision_ptr_end = revision_ptr + location_revisions->nelts;

  /* Ignore revisions R that are younger than the peg_revisions where
     path@peg_revision is not an ancestor of path@R. */
  is_ancestor = FALSE;
  while (revision_ptr < revision_ptr_end && *revision_ptr > peg_revision)
    {
      svn_pool_clear(currpool);
      SVN_ERR(check_ancestry_of_peg_path(&is_ancestor, fs, fs_path,
                                         peg_revision, *revision_ptr,
                                         currpool));
      if (is_ancestor)
        break;
      ++revision_ptr;
    }

  revision = is_ancestor ? *revision_ptr : peg_revision;
  path = fs_path;
  if (authz_read_func)
    {
      SVN_ERR(svn_fs_revision_root(&root, fs, revision, pool));
      SVN_ERR(check_readability(root, fs_path, authz_read_func,
                                authz_read_baton, pool));
    }

  while (revision_ptr < revision_ptr_end)
    {
      apr_pool_t *tmppool;
      svn_revnum_t appeared_rev, prev_rev;
      const char *prev_path;

      /* Find the target of the innermost copy relevant to path@revision.
         The copy may be of path itself, or of a parent directory. */
      SVN_ERR(svn_repos__prev_location(&appeared_rev, &prev_path, &prev_rev,
                                       fs, revision, path, currpool));
      if (! prev_path)
        break;

      /* Assign the current path to all younger revisions until we reach
         the copy target rev. */
      while ((revision_ptr < revision_ptr_end)
             && (*revision_ptr >= appeared_rev))
        {
          /* *revision_ptr is allocated out of pool, so we can point
             to in the hash table. */
          apr_hash_set(*locations, revision_ptr, sizeof(*revision_ptr),
                       apr_pstrdup(pool, path));
          revision_ptr++;
        }

      /* Ignore all revs between the copy target rev and the copy
         source rev (non-inclusive). */
      while ((revision_ptr < revision_ptr_end)
             && (*revision_ptr > prev_rev))
        revision_ptr++;

      /* State update. */
      path = prev_path;
      revision = prev_rev;

      if (authz_read_func)
        {
          svn_boolean_t readable;
          SVN_ERR(svn_fs_revision_root(&root, fs, revision, currpool));
          SVN_ERR(authz_read_func(&readable, root, path,
                                  authz_read_baton, currpool));
          if (!readable)
            {
              svn_pool_destroy(lastpool);
              svn_pool_destroy(currpool);
              return SVN_NO_ERROR;
            }
        }

      /* Clear last pool and switch. */
      svn_pool_clear(lastpool);
      tmppool = lastpool;
      lastpool = currpool;
      currpool = tmppool;
    }

  /* There are no copies relevant to path@revision.  So any remaining
     revisions either predate the creation of path@revision or have
     the node existing at the same path.  We will look up path@lrev
     for each remaining location-revision and make sure it is related
     to path@revision. */
  SVN_ERR(svn_fs_revision_root(&root, fs, revision, lastpool));
  while (revision_ptr < revision_ptr_end)
    {
      svn_node_kind_t kind;
      svn_fs_node_relation_t node_relation;
      svn_fs_root_t *cur_rev_root;

      svn_pool_clear(currpool);
      SVN_ERR(svn_fs_revision_root(&cur_rev_root, fs, *revision_ptr,
                                   currpool));
      SVN_ERR(svn_fs_check_path(&kind, cur_rev_root, path, currpool));
      if (kind == svn_node_none)
        break;
      SVN_ERR(svn_fs_node_relation(&node_relation, root, path,
                                   cur_rev_root, path, currpool));
      if (node_relation == svn_fs_node_unrelated)
        break;

      /* The node exists at the same path; record that and advance. */
      apr_hash_set(*locations, revision_ptr, sizeof(*revision_ptr),
                   apr_pstrdup(pool, path));
      revision_ptr++;
    }

  /* Ignore any remaining location-revisions; they predate the
     creation of path@revision. */

  svn_pool_destroy(lastpool);
  svn_pool_destroy(currpool);

  return SVN_NO_ERROR;
}