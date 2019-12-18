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
typedef  int /*<<< orphan*/  svn_commit_callback_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
struct commit_wrapper_baton {int /*<<< orphan*/  callback; void* baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct commit_wrapper_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  commit_wrapper_callback ; 

void
svn_compat_wrap_commit_callback(svn_commit_callback2_t *callback2,
                                void **callback2_baton,
                                svn_commit_callback_t callback,
                                void *callback_baton,
                                apr_pool_t *pool)
{
  struct commit_wrapper_baton *cwb = apr_palloc(pool, sizeof(*cwb));

  /* Set the user provided old format callback in the baton */
  cwb->baton = callback_baton;
  cwb->callback = callback;

  *callback2_baton = cwb;
  *callback2 = commit_wrapper_callback;
}