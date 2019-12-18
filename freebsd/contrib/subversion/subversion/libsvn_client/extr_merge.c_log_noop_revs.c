#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_14__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ svn_rangelist_t ;
struct TYPE_15__ {int /*<<< orphan*/  changed_paths2; scalar_t__ revision; } ;
typedef  TYPE_3__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_16__ {scalar_t__ pre_merge_mergeinfo; } ;
typedef  TYPE_4__ svn_client__merge_path_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_17__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  merged_ranges; TYPE_1__* target; int /*<<< orphan*/  children_with_mergeinfo; int /*<<< orphan*/  source_fspath; int /*<<< orphan*/  operative_ranges; } ;
typedef  TYPE_5__ log_noop_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_13__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_4__* get_child_with_mergeinfo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rangelist_merge_revision (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* svn_hash_gets (scalar_t__,char const*) ; 
 TYPE_2__* svn_rangelist__initialize (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rangelist_intersect (TYPE_2__**,TYPE_2__*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
log_noop_revs(void *baton,
              svn_log_entry_t *log_entry,
              apr_pool_t *scratch_pool)
{
  log_noop_baton_t *log_gap_baton = baton;
  apr_hash_index_t *hi;
  svn_revnum_t revision;
  svn_boolean_t log_entry_rev_required = FALSE;

  revision = log_entry->revision;

  /* It's possible that authz restrictions on the merge source prevent us
     from knowing about any of the changes for LOG_ENTRY->REVISION. */
  if (!log_entry->changed_paths2)
    return SVN_NO_ERROR;

  /* Unconditionally add LOG_ENTRY->REVISION to BATON->OPERATIVE_MERGES. */
  SVN_ERR(rangelist_merge_revision(log_gap_baton->operative_ranges,
                                   revision,
                                   log_gap_baton->pool));

  /* Examine each path affected by LOG_ENTRY->REVISION.  If the explicit or
     inherited mergeinfo for *all* of the corresponding paths under
     BATON->target->abspath reflects that LOG_ENTRY->REVISION has been
     merged, then add LOG_ENTRY->REVISION to BATON->MERGED_RANGES. */
  for (hi = apr_hash_first(scratch_pool, log_entry->changed_paths2);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *fspath = apr_hash_this_key(hi);
      const char *rel_path;
      const char *cwmi_abspath;
      svn_rangelist_t *paths_explicit_rangelist = NULL;
      svn_boolean_t mergeinfo_inherited = FALSE;

      /* Adjust REL_PATH so it is relative to the merge source then use it to
         calculate what path in the merge target would be affected by this
         revision. */
      rel_path = svn_fspath__skip_ancestor(log_gap_baton->source_fspath,
                                           fspath);
      /* Is PATH even within the merge target?  If it isn't we
         can disregard it altogether. */
      if (rel_path == NULL)
        continue;
      cwmi_abspath = svn_dirent_join(log_gap_baton->target->abspath,
                                     rel_path, scratch_pool);

      /* Find any explicit or inherited mergeinfo for PATH. */
      while (!log_entry_rev_required)
        {
          svn_client__merge_path_t *child = get_child_with_mergeinfo(
            log_gap_baton->children_with_mergeinfo, cwmi_abspath);

          if (child && child->pre_merge_mergeinfo)
            {
              /* Found some explicit mergeinfo, grab any ranges
                 for PATH. */
              paths_explicit_rangelist =
                            svn_hash_gets(child->pre_merge_mergeinfo, fspath);
              break;
            }

          if (cwmi_abspath[0] == '\0'
              || svn_dirent_is_root(cwmi_abspath, strlen(cwmi_abspath))
              || strcmp(log_gap_baton->target->abspath, cwmi_abspath) == 0)
            {
              /* Can't crawl any higher. */
              break;
            }

          /* Didn't find anything so crawl up to the parent. */
          cwmi_abspath = svn_dirent_dirname(cwmi_abspath, scratch_pool);
          fspath = svn_fspath__dirname(fspath, scratch_pool);

          /* At this point *if* we find mergeinfo it will be inherited. */
          mergeinfo_inherited = TRUE;
        }

      if (paths_explicit_rangelist)
        {
          svn_rangelist_t *intersecting_range;
          svn_rangelist_t *rangelist;

          rangelist = svn_rangelist__initialize(revision - 1, revision, TRUE,
                                                scratch_pool);

          /* If PATH inherited mergeinfo we must consider inheritance in the
             event the inherited mergeinfo is actually non-inheritable. */
          SVN_ERR(svn_rangelist_intersect(&intersecting_range,
                                          paths_explicit_rangelist,
                                          rangelist,
                                          mergeinfo_inherited, scratch_pool));

          if (intersecting_range->nelts == 0)
            log_entry_rev_required = TRUE;
        }
      else
        {
          log_entry_rev_required = TRUE;
        }
    }

  if (!log_entry_rev_required)
    SVN_ERR(rangelist_merge_revision(log_gap_baton->merged_ranges,
                                     revision,
                                     log_gap_baton->pool));

  return SVN_NO_ERROR;
}