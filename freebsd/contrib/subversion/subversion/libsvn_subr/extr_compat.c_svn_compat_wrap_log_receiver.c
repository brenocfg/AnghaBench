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
typedef  int /*<<< orphan*/  svn_log_message_receiver_t ;
typedef  int /*<<< orphan*/  svn_log_entry_receiver_t ;
struct log_wrapper_baton {int /*<<< orphan*/  receiver; void* baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct log_wrapper_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_wrapper_callback ; 

void
svn_compat_wrap_log_receiver(svn_log_entry_receiver_t *receiver2,
                             void **receiver2_baton,
                             svn_log_message_receiver_t receiver,
                             void *receiver_baton,
                             apr_pool_t *pool)
{
  struct log_wrapper_baton *lwb = apr_palloc(pool, sizeof(*lwb));

  /* Set the user provided old format callback in the baton. */
  lwb->baton = receiver_baton;
  lwb->receiver = receiver;

  *receiver2_baton = lwb;
  *receiver2 = log_wrapper_callback;
}