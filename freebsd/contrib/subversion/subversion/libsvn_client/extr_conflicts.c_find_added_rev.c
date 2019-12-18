#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ svn_wc_notify_t ;
struct TYPE_9__ {int /*<<< orphan*/  path; int /*<<< orphan*/  range_start; } ;
typedef  TYPE_3__ svn_location_segment_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct find_added_rev_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  added_rev; int /*<<< orphan*/ * parent_repos_relpath; TYPE_1__* ctx; int /*<<< orphan*/  victim_abspath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_relpath_skip_ancestor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_wc_create_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict_details_progress ; 

__attribute__((used)) static svn_error_t *
find_added_rev(svn_location_segment_t *segment,
               void *baton,
               apr_pool_t *scratch_pool)
{
  struct find_added_rev_baton *b = baton;

  if (b->ctx->notify_func2)
    {
      svn_wc_notify_t *notify;

      notify = svn_wc_create_notify(
                 b->victim_abspath,
                 svn_wc_notify_tree_conflict_details_progress,
                 scratch_pool),
      notify->revision = segment->range_start;
      b->ctx->notify_func2(b->ctx->notify_baton2, notify, scratch_pool);
    }

  if (segment->path) /* not interested in gaps */
    {
      if (b->parent_repos_relpath == NULL ||
          svn_relpath_skip_ancestor(b->parent_repos_relpath,
                                    segment->path) != NULL)
        {
          b->added_rev = segment->range_start;
          b->repos_relpath = apr_pstrdup(b->pool, segment->path);
        }
    }

  return SVN_NO_ERROR;
}