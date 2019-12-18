#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_17__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_4__ svn_diff_source_t ;
struct svn_diff_tree_processor_t {TYPE_5__* baton; } ;
struct merge_file_baton_t {scalar_t__ tree_conflict_reason; int /*<<< orphan*/  add_is_replace; TYPE_8__* parent_baton; int /*<<< orphan*/  skip_reason; scalar_t__ shadowed; } ;
struct TYPE_15__ {TYPE_1__* loc2; scalar_t__ ancestral; } ;
struct TYPE_18__ {int /*<<< orphan*/ * use_sleep; TYPE_3__* ctx; int /*<<< orphan*/  pool; int /*<<< orphan*/  paths_with_new_mergeinfo; TYPE_12__* target; TYPE_2__ merge_source; scalar_t__ same_repos; int /*<<< orphan*/  dry_run; int /*<<< orphan*/  added_abspaths; scalar_t__ reintegrate_merge; scalar_t__ record_only; } ;
typedef  TYPE_5__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_19__ {int /*<<< orphan*/  added; } ;
struct TYPE_16__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  url; } ;
struct TYPE_13__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 scalar_t__ CONFLICT_REASON_NONE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  alloc_and_store_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_repos_match (TYPE_12__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_file_edited (TYPE_5__*,struct merge_file_baton_t*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_skip (TYPE_5__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_update_add (TYPE_5__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_path (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_categorize_props (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 char* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_array_to_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_hash_to_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_add_repos_file4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_shadowed_add ; 

__attribute__((used)) static svn_error_t *
merge_file_added(const char *relpath,
                 const svn_diff_source_t *copyfrom_source,
                 const svn_diff_source_t *right_source,
                 const char *copyfrom_file,
                 const char *right_file,
                 /*const*/ apr_hash_t *copyfrom_props,
                 /*const*/ apr_hash_t *right_props,
                 void *file_baton,
                 const struct svn_diff_tree_processor_t *processor,
                 apr_pool_t *scratch_pool)
{
  merge_cmd_baton_t *merge_b = processor->baton;
  struct merge_file_baton_t *fb = file_baton;
  const char *local_abspath = svn_dirent_join(merge_b->target->abspath,
                                              relpath, scratch_pool);
  apr_hash_t *pristine_props;
  apr_hash_t *new_props;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  SVN_ERR(mark_file_edited(merge_b, fb, local_abspath, scratch_pool));

  if (fb->shadowed)
    {
      if (fb->tree_conflict_reason == CONFLICT_REASON_NONE)
        {
          /* We haven't notified for this node yet: report a skip */
          SVN_ERR(record_skip(merge_b, local_abspath, svn_node_file,
                              svn_wc_notify_update_shadowed_add,
                              fb->skip_reason, fb->parent_baton,
                              scratch_pool));
        }

      return SVN_NO_ERROR;
    }

  /* Easy out: We are only applying mergeinfo differences. */
  if (merge_b->record_only)
    {
      return SVN_NO_ERROR;
    }

  if ((merge_b->merge_source.ancestral || merge_b->reintegrate_merge)
      && ( !fb->parent_baton || !fb->parent_baton->added))
    {
      /* Store the roots of added subtrees */
      store_path(merge_b->added_abspaths, local_abspath);
    }

  if (!merge_b->dry_run)
    {
      const char *copyfrom_url;
      svn_revnum_t copyfrom_rev;
      svn_stream_t *new_contents, *pristine_contents;

      /* If this is a merge from the same repository as our
         working copy, we handle adds as add-with-history.
         Otherwise, we'll use a pure add. */
      if (merge_b->same_repos)
        {
          copyfrom_url = svn_path_url_add_component2(
                                       merge_b->merge_source.loc2->url,
                                       relpath, scratch_pool);
          copyfrom_rev = right_source->revision;
          SVN_ERR(check_repos_match(merge_b->target, local_abspath,
                                    copyfrom_url, scratch_pool));
          SVN_ERR(svn_stream_open_readonly(&pristine_contents,
                                           right_file,
                                           scratch_pool,
                                           scratch_pool));
          new_contents = NULL; /* inherit from new_base_contents */

          pristine_props = right_props; /* Includes last_* information */
          new_props = NULL; /* No local changes */

          if (svn_hash_gets(pristine_props, SVN_PROP_MERGEINFO))
            {
              alloc_and_store_path(&merge_b->paths_with_new_mergeinfo,
                                   local_abspath, merge_b->pool);
            }
        }
      else
        {
          apr_array_header_t *regular_props;

          copyfrom_url = NULL;
          copyfrom_rev = SVN_INVALID_REVNUM;

          pristine_contents = svn_stream_empty(scratch_pool);
          SVN_ERR(svn_stream_open_readonly(&new_contents, right_file,
                                           scratch_pool, scratch_pool));

          pristine_props = apr_hash_make(scratch_pool); /* Local addition */

          /* We don't want any foreign properties */
          SVN_ERR(svn_categorize_props(svn_prop_hash_to_array(right_props,
                                                              scratch_pool),
                                       NULL, NULL, &regular_props,
                                       scratch_pool));

          new_props = svn_prop_array_to_hash(regular_props, scratch_pool);

          /* Issue #3383: We don't want mergeinfo from a foreign repository. */
          svn_hash_sets(new_props, SVN_PROP_MERGEINFO, NULL);
        }

      /* Do everything like if we had called 'svn cp PATH1 PATH2'. */
      SVN_ERR(svn_wc_add_repos_file4(merge_b->ctx->wc_ctx,
                                      local_abspath,
                                      pristine_contents,
                                      new_contents,
                                      pristine_props, new_props,
                                      copyfrom_url, copyfrom_rev,
                                      merge_b->ctx->cancel_func,
                                      merge_b->ctx->cancel_baton,
                                      scratch_pool));

      /* Caller must call svn_sleep_for_timestamps() */
      *merge_b->use_sleep = TRUE;
    }

  SVN_ERR(record_update_add(merge_b, local_abspath, svn_node_file,
                            fb->add_is_replace, scratch_pool));

  return SVN_NO_ERROR;
}