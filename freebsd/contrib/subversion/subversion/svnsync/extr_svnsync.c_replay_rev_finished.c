#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* close_edit ) (void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ svn_delta_editor_t ;
struct TYPE_7__ {int normalized_rev_props_count; TYPE_1__* sb; scalar_t__ has_atomic_revprops_capability; int /*<<< orphan*/  to_session; scalar_t__ has_commit_revprops_capability; } ;
typedef  TYPE_3__ replay_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_5__ {int /*<<< orphan*/  quiet; int /*<<< orphan*/  source_prop_encoding; int /*<<< orphan*/  committed_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int /*<<< orphan*/  SVNSYNC_PROP_CURRENTLY_COPYING ; 
 int /*<<< orphan*/  SVNSYNC_PROP_LAST_MERGED_REV ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  filter_exclude_log ; 
 int /*<<< orphan*/  filter_include_date_author_sync ; 
 int /*<<< orphan*/ * filter_props (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_properties_copied (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_props_not_in_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_change_rev_prop2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_rev_proplist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_createf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svnsync_normalize_revprops (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_revprops (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
replay_rev_finished(svn_revnum_t revision,
                    void *replay_baton,
                    const svn_delta_editor_t *editor,
                    void *edit_baton,
                    apr_hash_t *rev_props,
                    apr_pool_t *pool)
{
  apr_pool_t *subpool = svn_pool_create(pool);
  replay_baton_t *rb = replay_baton;
  apr_hash_t *filtered, *existing_props;
  int filtered_count;
  int normalized_count;
  const svn_string_t *rev_str;

  SVN_ERR(editor->close_edit(edit_baton, pool));

  /* Sanity check that we actually committed the revision we meant to. */
  if (rb->sb->committed_rev != revision)
    return svn_error_createf
             (APR_EINVAL, NULL,
              _("Commit created r%ld but should have created r%ld"),
              rb->sb->committed_rev, revision);

  SVN_ERR(svn_ra_rev_proplist(rb->to_session, revision, &existing_props,
                              subpool));


  /* Ok, we're done with the data, now we just need to copy the remaining
     'svn:date' and 'svn:author' revprops and we're all set.
     If the server doesn't support revprops-in-a-commit, we still have to
     set all revision properties except svn:log. */
  filtered = filter_props(&filtered_count, rev_props,
                          (rb->has_commit_revprops_capability
                            ? filter_include_date_author_sync
                            : filter_exclude_log),
                          subpool);

  /* If necessary, normalize encoding and line ending style, and add the number
     of EOL-normalized properties to the overall count in the replay baton. */
  SVN_ERR(svnsync_normalize_revprops(filtered, &normalized_count,
                                     rb->sb->source_prop_encoding, pool));
  rb->normalized_rev_props_count += normalized_count;

  SVN_ERR(write_revprops(&filtered_count, rb->to_session, revision, filtered,
                         NULL, subpool));

  /* Remove all extra properties in TARGET. */
  SVN_ERR(remove_props_not_in_source(rb->to_session, revision,
                                     rev_props, existing_props, subpool));

  svn_pool_clear(subpool);

  rev_str = svn_string_createf(subpool, "%ld", revision);

  /* Ok, we're done, bring the last-merged-rev property up to date. */
  SVN_ERR(svn_ra_change_rev_prop2(
           rb->to_session,
           0,
           SVNSYNC_PROP_LAST_MERGED_REV,
           NULL,
           rev_str,
           subpool));

  /* And finally drop the currently copying prop, since we're done
     with this revision. */
  SVN_ERR(svn_ra_change_rev_prop2(rb->to_session, 0,
                                  SVNSYNC_PROP_CURRENTLY_COPYING,
                                  rb->has_atomic_revprops_capability
                                    ? &rev_str : NULL,
                                  NULL, subpool));

  /* Notify the user that we copied revision properties. */
  if (! rb->sb->quiet)
    SVN_ERR(log_properties_copied(filtered_count > 0, revision, subpool));

  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}