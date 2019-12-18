#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_diff_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct diff_callbacks2_wrapper_baton {void* baton; int /*<<< orphan*/  const* callbacks2; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 struct diff_callbacks2_wrapper_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  diff_callbacks2_wrapper ; 
 int /*<<< orphan*/ * svn_wc_diff5 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,struct diff_callbacks2_wrapper_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_diff4(svn_wc_adm_access_t *anchor,
             const char *target,
             const svn_wc_diff_callbacks2_t *callbacks,
             void *callback_baton,
             svn_depth_t depth,
             svn_boolean_t ignore_ancestry,
             const apr_array_header_t *changelist_filter,
             apr_pool_t *pool)
{
  struct diff_callbacks2_wrapper_baton *b = apr_palloc(pool, sizeof(*b));
  b->callbacks2 = callbacks;
  b->baton = callback_baton;

  return svn_wc_diff5(anchor, target, &diff_callbacks2_wrapper, b,
                      depth, ignore_ancestry, changelist_filter, pool);
}