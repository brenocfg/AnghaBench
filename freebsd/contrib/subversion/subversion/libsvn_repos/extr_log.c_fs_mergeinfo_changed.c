#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change_iterator_t ;
struct TYPE_9__ {char* data; } ;
struct TYPE_11__ {scalar_t__ mergeinfo_mod; int change_kind; char* copyfrom_path; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_known; TYPE_1__ path; scalar_t__ prop_mod; } ;
typedef  TYPE_3__ svn_fs_path_change3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ TRUE ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs__get_mergeinfo_for_path (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_copied_from (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_prop (TYPE_2__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  svn_fs_path_change_add 132 
#define  svn_fs_path_change_delete 131 
 int /*<<< orphan*/  svn_fs_path_change_get (TYPE_3__**,int /*<<< orphan*/ *) ; 
#define  svn_fs_path_change_modify 130 
#define  svn_fs_path_change_replace 129 
#define  svn_fs_path_change_reset 128 
 int /*<<< orphan*/  svn_fs_paths_changed3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_diff2 (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_inherited ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_to_string (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__prev_location (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_string_compare (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ svn_tristate_false ; 

__attribute__((used)) static svn_error_t *
fs_mergeinfo_changed(svn_mergeinfo_catalog_t *deleted_mergeinfo_catalog,
                     svn_mergeinfo_catalog_t *added_mergeinfo_catalog,
                     svn_fs_t *fs,
                     svn_revnum_t rev,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  svn_fs_root_t *root;
  apr_pool_t *iterpool, *iterator_pool;
  svn_fs_path_change_iterator_t *iterator;
  svn_fs_path_change3_t *change;
  svn_boolean_t any_mergeinfo = FALSE;
  svn_boolean_t any_copy = FALSE;

  /* Initialize return variables. */
  *deleted_mergeinfo_catalog = svn_hash__make(result_pool);
  *added_mergeinfo_catalog = svn_hash__make(result_pool);

  /* Revision 0 has no mergeinfo and no mergeinfo changes. */
  if (rev == 0)
    return SVN_NO_ERROR;

  /* FS iterators are potentially heavy objects.
   * Hold them in a separate pool to clean them up asap. */
  iterator_pool = svn_pool_create(scratch_pool);

  /* We're going to use the changed-paths information for REV to
     narrow down our search. */
  SVN_ERR(svn_fs_revision_root(&root, fs, rev, scratch_pool));
  SVN_ERR(svn_fs_paths_changed3(&iterator, root, iterator_pool,
                                iterator_pool));
  SVN_ERR(svn_fs_path_change_get(&change, iterator));

  /* Look for copies and (potential) mergeinfo changes.
     We will use both flags to take shortcuts further down the road.

     The critical information here is whether there are any copies
     because that greatly influences the costs for log processing.
     So, it is faster to iterate over the changes twice - in the worst
     case b/c most times there is no m/i at all and we exit out early
     without any overhead. 
   */
  while (change && (!any_mergeinfo || !any_copy))
    {
      /* If there was a prop change and we are not positive that _no_
         mergeinfo change happened, we must assume that it might have. */
      if (change->mergeinfo_mod != svn_tristate_false && change->prop_mod)
        any_mergeinfo = TRUE;

      if (   (change->change_kind == svn_fs_path_change_add)
          || (change->change_kind == svn_fs_path_change_replace))
        any_copy = TRUE;

      SVN_ERR(svn_fs_path_change_get(&change, iterator));
    }

  /* No potential mergeinfo changes?  We're done. */
  if (! any_mergeinfo)
    {
      svn_pool_destroy(iterator_pool);
      return SVN_NO_ERROR;
    }

  /* There is or may be some m/i change. Look closely now. */
  svn_pool_clear(iterator_pool);
  SVN_ERR(svn_fs_paths_changed3(&iterator, root, iterator_pool,
                                iterator_pool));

  /* Loop over changes, looking for anything that might carry an
     svn:mergeinfo change and is one of our paths of interest, or a
     child or [grand]parent directory thereof. */
  iterpool = svn_pool_create(scratch_pool);
  while (TRUE)
    {
      const char *changed_path;
      const char *base_path = NULL;
      svn_revnum_t base_rev = SVN_INVALID_REVNUM;
      svn_fs_root_t *base_root = NULL;
      svn_string_t *prev_mergeinfo_value = NULL, *mergeinfo_value;

      /* Next change. */
      SVN_ERR(svn_fs_path_change_get(&change, iterator));
      if (!change)
        break;

      /* Cheap pre-checks that don't require memory allocation etc. */

      /* No mergeinfo change? -> nothing to do here. */
      if (change->mergeinfo_mod == svn_tristate_false)
        continue;

      /* If there was no property change on this item, ignore it. */
      if (! change->prop_mod)
        continue;

      /* Begin actual processing */
      changed_path = change->path.data;
      svn_pool_clear(iterpool);

      switch (change->change_kind)
        {

        /* ### TODO: Can the add, replace, and modify cases be joined
           ### together to all use svn_repos__prev_location()?  The
           ### difference would be the fallback case (path/rev-1 for
           ### modifies, NULL otherwise).  -- cmpilato  */

        /* If the path was merely modified, see if its previous
           location was affected by a copy which happened in this
           revision before assuming it holds the same path it did the
           previous revision. */
        case svn_fs_path_change_modify:
          {
            svn_revnum_t appeared_rev;

            /* If there were no copies in this revision, the path will have
               existed in the previous rev.  Otherwise, we might just got
               copied here and need to check for that eventuality. */
            if (any_copy)
              {
                SVN_ERR(svn_repos__prev_location(&appeared_rev, &base_path,
                                                 &base_rev, fs, rev,
                                                 changed_path, iterpool));

                /* If this path isn't the result of a copy that occurred
                   in this revision, we can find the previous version of
                   it in REV - 1 at the same path. */
                if (! (base_path && SVN_IS_VALID_REVNUM(base_rev)
                      && (appeared_rev == rev)))
                  {
                    base_path = changed_path;
                    base_rev = rev - 1;
                  }
              }
            else
              {
                base_path = changed_path;
                base_rev = rev - 1;
              }
            break;
          }

        /* If the path was added or replaced, see if it was created via
           copy.  If so, set BASE_REV/BASE_PATH to its previous location.
           If not, there's no previous location to examine -- leave
           BASE_REV/BASE_PATH = -1/NULL.  */
        case svn_fs_path_change_add:
        case svn_fs_path_change_replace:
          {
            if (change->copyfrom_known)
              {
                base_rev = change->copyfrom_rev;
                base_path = change->copyfrom_path;
              }
            else
              {
                SVN_ERR(svn_fs_copied_from(&base_rev, &base_path,
                                          root, changed_path, iterpool));
              }
            break;
          }

        /* We don't care about any of the other cases. */
        case svn_fs_path_change_delete:
        case svn_fs_path_change_reset:
        default:
          continue;
        }

      /* If there was a base location, fetch its mergeinfo property value. */
      if (base_path && SVN_IS_VALID_REVNUM(base_rev))
        {
          SVN_ERR(svn_fs_revision_root(&base_root, fs, base_rev, iterpool));
          SVN_ERR(svn_fs_node_prop(&prev_mergeinfo_value, base_root, base_path,
                                   SVN_PROP_MERGEINFO, iterpool));
        }

      /* Now fetch the current (as of REV) mergeinfo property value. */
      SVN_ERR(svn_fs_node_prop(&mergeinfo_value, root, changed_path,
                               SVN_PROP_MERGEINFO, iterpool));

      /* No mergeinfo on either the new or previous location?  Just
         skip it.  (If there *was* a change, it would have been in
         inherited mergeinfo only, which should be picked up by the
         iteration of this loop that finds the parent paths that
         really got changed.)  */
      if (! (mergeinfo_value || prev_mergeinfo_value))
        continue;

      /* Mergeinfo on both sides but it did not change? Skip that too. */
      if (   mergeinfo_value && prev_mergeinfo_value
          && svn_string_compare(mergeinfo_value, prev_mergeinfo_value))
        continue;

      /* If mergeinfo was explicitly added or removed on this path, we
         need to check to see if that was a real semantic change of
         meaning.  So, fill in the "missing" mergeinfo value with the
         inherited mergeinfo for that path/revision.  */
      if (prev_mergeinfo_value && (! mergeinfo_value))
        {
          svn_mergeinfo_t tmp_mergeinfo;

          SVN_ERR(svn_fs__get_mergeinfo_for_path(&tmp_mergeinfo,
                                                 root, changed_path,
                                                 svn_mergeinfo_inherited, TRUE,
                                                 iterpool, iterpool));
          if (tmp_mergeinfo)
            SVN_ERR(svn_mergeinfo_to_string(&mergeinfo_value,
                                            tmp_mergeinfo,
                                            iterpool));
        }
      else if (mergeinfo_value && (! prev_mergeinfo_value)
               && base_path && SVN_IS_VALID_REVNUM(base_rev))
        {
          svn_mergeinfo_t tmp_mergeinfo;

          SVN_ERR(svn_fs__get_mergeinfo_for_path(&tmp_mergeinfo,
                                                 base_root, base_path,
                                                 svn_mergeinfo_inherited, TRUE,
                                                 iterpool, iterpool));
          if (tmp_mergeinfo)
            SVN_ERR(svn_mergeinfo_to_string(&prev_mergeinfo_value,
                                            tmp_mergeinfo,
                                            iterpool));
        }

      /* Old and new mergeinfo probably differ in some way (we already
         checked for textual equality further up). Store the before and
         after mergeinfo values in our return hashes.  They may still be
         equal as manual intervention may have only changed the formatting
         but not the relevant contents. */
        {
          svn_mergeinfo_t prev_mergeinfo = NULL, mergeinfo = NULL;
          svn_mergeinfo_t deleted, added;
          const char *hash_path;

          if (mergeinfo_value)
            SVN_ERR(svn_mergeinfo_parse(&mergeinfo,
                                        mergeinfo_value->data, iterpool));
          if (prev_mergeinfo_value)
            SVN_ERR(svn_mergeinfo_parse(&prev_mergeinfo,
                                        prev_mergeinfo_value->data, iterpool));
          SVN_ERR(svn_mergeinfo_diff2(&deleted, &added, prev_mergeinfo,
                                      mergeinfo, FALSE, result_pool,
                                      iterpool));

          /* Toss interesting stuff into our return catalogs. */
          hash_path = apr_pstrdup(result_pool, changed_path);
          svn_hash_sets(*deleted_mergeinfo_catalog, hash_path, deleted);
          svn_hash_sets(*added_mergeinfo_catalog, hash_path, added);
        }
    }

  svn_pool_destroy(iterpool);
  svn_pool_destroy(iterator_pool);

  return SVN_NO_ERROR;
}