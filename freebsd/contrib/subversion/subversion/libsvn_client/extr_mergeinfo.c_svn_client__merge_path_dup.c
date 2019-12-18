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
struct TYPE_6__ {void* implicit_mergeinfo; void* pre_merge_mergeinfo; scalar_t__ remaining_ranges; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_client__merge_path_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* svn_mergeinfo_dup (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_rangelist_dup (scalar_t__,int /*<<< orphan*/ *) ; 

svn_client__merge_path_t *
svn_client__merge_path_dup(const svn_client__merge_path_t *old,
                           apr_pool_t *pool)
{
  svn_client__merge_path_t *new = apr_pmemdup(pool, old, sizeof(*old));

  new->abspath = apr_pstrdup(pool, old->abspath);
  if (new->remaining_ranges)
    new->remaining_ranges = svn_rangelist_dup(old->remaining_ranges, pool);
  if (new->pre_merge_mergeinfo)
    new->pre_merge_mergeinfo = svn_mergeinfo_dup(old->pre_merge_mergeinfo,
                                                 pool);
  if (new->implicit_mergeinfo)
    new->implicit_mergeinfo = svn_mergeinfo_dup(old->implicit_mergeinfo,
                                                pool);

  return new;
}