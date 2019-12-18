#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * merge_range; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_merge_range_t ;
struct TYPE_7__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_merge_range_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_merge_record_info_begin ; 

__attribute__((used)) static void
notify_mergeinfo_recording(const char *target_abspath,
                           const svn_merge_range_t *range,
                           svn_client_ctx_t *ctx,
                           apr_pool_t *pool)
{
  if (ctx->notify_func2)
    {
      svn_wc_notify_t *n = svn_wc_create_notify(
        target_abspath, svn_wc_notify_merge_record_info_begin, pool);

      n->merge_range = range ? svn_merge_range_dup(range, pool) : NULL;
      ctx->notify_func2(ctx->notify_baton2, n, pool);
    }
}