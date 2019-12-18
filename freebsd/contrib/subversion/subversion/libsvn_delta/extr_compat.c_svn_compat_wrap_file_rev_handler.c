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
typedef  int /*<<< orphan*/  svn_file_rev_handler_t ;
typedef  int /*<<< orphan*/  svn_file_rev_handler_old_t ;
struct file_rev_handler_wrapper_baton {int /*<<< orphan*/  handler; void* baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct file_rev_handler_wrapper_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  file_rev_handler_wrapper ; 

void
svn_compat_wrap_file_rev_handler(svn_file_rev_handler_t *handler2,
                                 void **handler2_baton,
                                 svn_file_rev_handler_old_t handler,
                                 void *handler_baton,
                                 apr_pool_t *pool)
{
  struct file_rev_handler_wrapper_baton *fwb = apr_pcalloc(pool, sizeof(*fwb));

  /* Set the user provided old format callback in the baton. */
  fwb->baton = handler_baton;
  fwb->handler = handler;

  *handler2_baton = fwb;
  *handler2 = file_rev_handler_wrapper;
}