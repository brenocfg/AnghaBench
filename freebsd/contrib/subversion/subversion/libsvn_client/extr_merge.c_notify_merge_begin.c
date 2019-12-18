#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_7__* merge_range; } ;
typedef  TYPE_6__ svn_wc_notify_t ;
struct TYPE_22__ {int /*<<< orphan*/  start; int /*<<< orphan*/  end; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ svn_merge_range_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_23__ {char* abspath; TYPE_2__* remaining_ranges; scalar_t__ absent; } ;
typedef  TYPE_8__ svn_client__merge_path_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_18__ {char* last_abspath; int /*<<< orphan*/  nodes_with_mergeinfo; } ;
struct TYPE_16__ {scalar_t__ ancestral; } ;
struct TYPE_24__ {TYPE_5__* ctx; int /*<<< orphan*/  implicit_src_gap; scalar_t__ same_repos; TYPE_4__* target; TYPE_3__ notify_begin; TYPE_1__ merge_source; } ;
typedef  TYPE_9__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_20__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_19__ {char* abspath; } ;
struct TYPE_17__ {scalar_t__ nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_8__* find_nearest_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 TYPE_8__* find_nearest_ancestor_with_intersecting_ranges (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  remove_source_gap (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_foreign_merge_begin ; 
 int /*<<< orphan*/  svn_wc_notify_merge_begin ; 

__attribute__((used)) static svn_error_t *
notify_merge_begin(merge_cmd_baton_t *merge_b,
                   const char *local_abspath,
                   svn_boolean_t delete_action,
                   apr_pool_t *scratch_pool)
{
  svn_wc_notify_t *notify;
  svn_merge_range_t n_range =
    {SVN_INVALID_REVNUM, SVN_INVALID_REVNUM, TRUE};
  const char *notify_abspath;

  if (! merge_b->ctx->notify_func2)
    return SVN_NO_ERROR;

  /* If our merge sources are ancestors of one another... */
  if (merge_b->merge_source.ancestral)
    {
      const svn_client__merge_path_t *child;
      /* Find NOTIFY->PATH's nearest ancestor in
         NOTIFY->CHILDREN_WITH_MERGEINFO.  Normally we consider a child in
         NOTIFY->CHILDREN_WITH_MERGEINFO representing PATH to be an
         ancestor of PATH, but if this is a deletion of PATH then the
         notification must be for a proper ancestor of PATH.  This ensures
         we don't get notifications like:

           --- Merging rX into 'PARENT/CHILD'
           D    PARENT/CHILD

         But rather:

           --- Merging rX into 'PARENT'
           D    PARENT/CHILD
      */

      child = find_nearest_ancestor_with_intersecting_ranges(
        &(n_range.start), &(n_range.end),
        merge_b->notify_begin.nodes_with_mergeinfo,
        ! delete_action, local_abspath);

      if (!child && delete_action)
        {
          /* Triggered by file replace in single-file-merge */
          child = find_nearest_ancestor(merge_b->notify_begin.nodes_with_mergeinfo,
                                        TRUE, local_abspath);
        }

      assert(child != NULL); /* Should always find the merge anchor */

      if (! child)
        return SVN_NO_ERROR;

      if (merge_b->notify_begin.last_abspath != NULL
          && strcmp(child->abspath, merge_b->notify_begin.last_abspath) == 0)
        {
          /* Don't notify the same merge again */
          return SVN_NO_ERROR;
        }

      merge_b->notify_begin.last_abspath = child->abspath;

      if (child->absent || child->remaining_ranges->nelts == 0
          || !SVN_IS_VALID_REVNUM(n_range.start))
        {
          /* No valid information for an header */
          return SVN_NO_ERROR;
        }

      notify_abspath = child->abspath;
    }
  else
    {
      if (merge_b->notify_begin.last_abspath)
        return SVN_NO_ERROR; /* already notified */

      notify_abspath = merge_b->target->abspath;
      /* Store something in last_abspath. Any value would do */
      merge_b->notify_begin.last_abspath = merge_b->target->abspath;
    }

  notify = svn_wc_create_notify(notify_abspath,
                                merge_b->same_repos
                                      ? svn_wc_notify_merge_begin
                                      : svn_wc_notify_foreign_merge_begin,
                                scratch_pool);

  if (SVN_IS_VALID_REVNUM(n_range.start))
    {
      /* If the merge source has a gap, then don't mention
         those gap revisions in the notification. */
      remove_source_gap(&n_range, merge_b->implicit_src_gap);
      notify->merge_range = &n_range;
    }
  else
    {
      notify->merge_range = NULL;
    }

  merge_b->ctx->notify_func2(merge_b->ctx->notify_baton2, notify,
                             scratch_pool);

  return SVN_NO_ERROR;
}