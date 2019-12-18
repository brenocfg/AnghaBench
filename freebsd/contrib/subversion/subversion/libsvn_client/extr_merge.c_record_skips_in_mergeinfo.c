#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_merge_range_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; TYPE_1__* target; int /*<<< orphan*/  skipped_abspaths; } ;
typedef  TYPE_2__ merge_cmd_baton_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_5__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perform_obstruction_check (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_notify_state_missing ; 
 scalar_t__ svn_wc_notify_state_obstructed ; 
 int /*<<< orphan*/  update_wc_mergeinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
record_skips_in_mergeinfo(const char *mergeinfo_path,
                          const svn_rangelist_t *rangelist,
                          svn_boolean_t is_rollback,
                          merge_cmd_baton_t *merge_b,
                          apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  apr_hash_t *merges;
  apr_size_t nbr_skips = apr_hash_count(merge_b->skipped_abspaths);
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  if (nbr_skips == 0)
    return SVN_NO_ERROR;

  merges = apr_hash_make(scratch_pool);

  /* Override the mergeinfo for child paths which weren't actually merged. */
  for (hi = apr_hash_first(scratch_pool, merge_b->skipped_abspaths); hi;
       hi = apr_hash_next(hi))
    {
      const char *skipped_abspath = apr_hash_this_key(hi);
      svn_wc_notify_state_t obstruction_state;

      svn_pool_clear(iterpool);

      /* Before we override, make sure this is a versioned path, it might
         be an external or missing from disk due to authz restrictions. */
      SVN_ERR(perform_obstruction_check(&obstruction_state, NULL, NULL,
                                        NULL, NULL,
                                        merge_b, skipped_abspath,
                                        iterpool));
      if (obstruction_state == svn_wc_notify_state_obstructed
          || obstruction_state == svn_wc_notify_state_missing)
        continue;

      /* Add an empty range list for this path.

         ### TODO: This works fine for a file path skipped because it is
         ### missing as long as the file's parent directory is present.
         ### But missing directory paths skipped are not handled yet,
         ### see issue #2915.

         ### TODO: An empty range is fine if the skipped path doesn't
         ### inherit any mergeinfo from a parent, but if it does
         ### we need to account for that.  See issue #3440
         ### http://subversion.tigris.org/issues/show_bug.cgi?id=3440. */
      svn_hash_sets(merges, skipped_abspath,
                    apr_array_make(scratch_pool, 0,
                                   sizeof(svn_merge_range_t *)));

      /* if (nbr_skips < notify_b->nbr_notifications)
           ### Use RANGELIST as the mergeinfo for all children of
           ### this path which were not also explicitly
           ### skipped? */
    }
  SVN_ERR(update_wc_mergeinfo(NULL, merge_b->target->abspath,
                              mergeinfo_path, merges,
                              is_rollback, merge_b->ctx, iterpool));
  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}