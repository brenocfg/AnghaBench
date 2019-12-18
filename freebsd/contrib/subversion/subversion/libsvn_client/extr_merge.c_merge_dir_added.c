#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_17__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_4__ svn_diff_source_t ;
struct svn_diff_tree_processor_t {TYPE_5__* baton; } ;
struct merge_dir_baton_t {scalar_t__ tree_conflict_reason; TYPE_7__* parent_baton; scalar_t__ edited; int /*<<< orphan*/  skip_reason; scalar_t__ shadowed; } ;
struct TYPE_15__ {TYPE_1__* loc2; scalar_t__ ancestral; } ;
struct TYPE_18__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  conflicted_paths; TYPE_3__* ctx; int /*<<< orphan*/  dry_run; int /*<<< orphan*/  paths_with_new_mergeinfo; TYPE_12__* target; TYPE_2__ merge_source; scalar_t__ same_repos; int /*<<< orphan*/  added_abspaths; scalar_t__ reintegrate_merge; int /*<<< orphan*/  record_only; } ;
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
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  alloc_and_store_path (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_repos_match (TYPE_12__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_pending_notifications (TYPE_5__*,struct merge_dir_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_dir_edited (TYPE_5__*,struct merge_dir_baton_t*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_skip (TYPE_5__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_path (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_categorize_props (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_is_child (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 char* svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_array_to_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_hash_to_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__complete_directory_add (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_merge_props3 (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_notify_state_conflicted ; 
 int /*<<< orphan*/  svn_wc_notify_update_shadowed_add ; 

__attribute__((used)) static svn_error_t *
merge_dir_added(const char *relpath,
                const svn_diff_source_t *copyfrom_source,
                const svn_diff_source_t *right_source,
                /*const*/ apr_hash_t *copyfrom_props,
                /*const*/ apr_hash_t *right_props,
                void *dir_baton,
                const struct svn_diff_tree_processor_t *processor,
                apr_pool_t *scratch_pool)
{
  merge_cmd_baton_t *merge_b = processor->baton;
  struct merge_dir_baton_t *db = dir_baton;
  const char *local_abspath = svn_dirent_join(merge_b->target->abspath,
                                              relpath, scratch_pool);

  /* For consistency; usually a no-op from _dir_added() */
  SVN_ERR(handle_pending_notifications(merge_b, db, scratch_pool));
  SVN_ERR(mark_dir_edited(merge_b, db, local_abspath, scratch_pool));

  if (db->shadowed)
    {
      if (db->tree_conflict_reason == CONFLICT_REASON_NONE)
        {
          /* We haven't notified for this node yet: report a skip */
          SVN_ERR(record_skip(merge_b, local_abspath, svn_node_dir,
                              svn_wc_notify_update_shadowed_add,
                              db->skip_reason, db->parent_baton,
                              scratch_pool));
        }

      return SVN_NO_ERROR;
    }

  SVN_ERR_ASSERT(
                 db->edited                  /* Marked edited from merge_open_dir() */
                 && ! merge_b->record_only /* Skip details from merge_open_dir() */
                 );

  if ((merge_b->merge_source.ancestral || merge_b->reintegrate_merge)
      && ( !db->parent_baton || !db->parent_baton->added))
    {
      /* Store the roots of added subtrees */
      store_path(merge_b->added_abspaths, local_abspath);
    }

  if (merge_b->same_repos)
    {
      /* When the directory was added in merge_dir_added() we didn't update its
         pristine properties. Instead we receive the property changes later and
         apply them in this function.

         If we would apply them as changes (such as before fixing issue #3405),
         we would see the unmodified properties as local changes, and the
         pristine properties would be out of sync with what the repository
         expects for this directory.

         Instead of doing that we now simply set the properties as the pristine
         properties via a private libsvn_wc api.
      */

      const char *copyfrom_url;
      svn_revnum_t copyfrom_rev;
      const char *parent_abspath;
      const char *child;

      /* Creating a hash containing regular and entry props */
      apr_hash_t *new_pristine_props = right_props;

      parent_abspath = svn_dirent_dirname(local_abspath, scratch_pool);
      child = svn_dirent_is_child(merge_b->target->abspath, local_abspath, NULL);
      SVN_ERR_ASSERT(child != NULL);

      copyfrom_url = svn_path_url_add_component2(merge_b->merge_source.loc2->url,
                                                 child, scratch_pool);
      copyfrom_rev = right_source->revision;

      SVN_ERR(check_repos_match(merge_b->target, parent_abspath, copyfrom_url,
                                scratch_pool));

      if (!merge_b->dry_run)
        {
          SVN_ERR(svn_wc__complete_directory_add(merge_b->ctx->wc_ctx,
                                                local_abspath,
                                                new_pristine_props,
                                                copyfrom_url, copyfrom_rev,
                                                scratch_pool));
        }

      if (svn_hash_gets(new_pristine_props, SVN_PROP_MERGEINFO))
        {
          alloc_and_store_path(&merge_b->paths_with_new_mergeinfo,
                               local_abspath, merge_b->pool);
        }
    }
  else
    {
      apr_array_header_t *regular_props;
      apr_hash_t *new_props;
      svn_wc_notify_state_t prop_state;

      SVN_ERR(svn_categorize_props(svn_prop_hash_to_array(right_props,
                                                          scratch_pool),
                                   NULL, NULL, &regular_props, scratch_pool));

      new_props = svn_prop_array_to_hash(regular_props, scratch_pool);

      svn_hash_sets(new_props, SVN_PROP_MERGEINFO, NULL);

      /* ### What is the easiest way to set new_props on LOCAL_ABSPATH?

         ### This doesn't need a merge as we just added the node
         ### (or installed a tree conflict and skipped this node)*/

      SVN_ERR(svn_wc_merge_props3(&prop_state, merge_b->ctx->wc_ctx,
                                  local_abspath,
                                  NULL, NULL,
                                  apr_hash_make(scratch_pool),
                                  svn_prop_hash_to_array(new_props,
                                                         scratch_pool),
                                  merge_b->dry_run,
                                  NULL, NULL,
                                  merge_b->ctx->cancel_func,
                                  merge_b->ctx->cancel_baton,
                                  scratch_pool));
      if (prop_state == svn_wc_notify_state_conflicted)
        {
          alloc_and_store_path(&merge_b->conflicted_paths, local_abspath,
                               merge_b->pool);
        }
    }

  return SVN_NO_ERROR;
}