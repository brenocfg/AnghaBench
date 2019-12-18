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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
typedef  int /*<<< orphan*/  svn_diff_fns_t ;
typedef  int /*<<< orphan*/  svn_diff_fns2_t ;
struct fns_wrapper_baton {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_diff_diff3_2 (int /*<<< orphan*/ **,struct fns_wrapper_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_diff_fns (int /*<<< orphan*/ **,struct fns_wrapper_baton**,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_diff_diff3(svn_diff_t **diff,
               void *diff_baton,
               const svn_diff_fns_t *vtable,
               apr_pool_t *pool)
{
  svn_diff_fns2_t *diff_fns2;
  struct fns_wrapper_baton *fwb;

  wrap_diff_fns(&diff_fns2, &fwb, vtable, diff_baton, pool);
  return svn_diff_diff3_2(diff, fwb, diff_fns2, pool);
}