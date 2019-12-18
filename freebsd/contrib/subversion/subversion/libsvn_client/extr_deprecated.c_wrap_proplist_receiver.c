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
typedef  int /*<<< orphan*/  svn_proplist_receiver_t ;
typedef  int /*<<< orphan*/  svn_proplist_receiver2_t ;
struct proplist_receiver_wrapper_baton {int /*<<< orphan*/  receiver; void* baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct proplist_receiver_wrapper_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proplist_wrapper_receiver ; 

__attribute__((used)) static void
wrap_proplist_receiver(svn_proplist_receiver2_t *receiver2,
                       void **receiver2_baton,
                       svn_proplist_receiver_t receiver,
                       void *receiver_baton,
                       apr_pool_t *pool)
{
  struct proplist_receiver_wrapper_baton *plrwb = apr_palloc(pool,
                                                             sizeof(*plrwb));

  /* Set the user provided old format callback in the baton. */
  plrwb->baton = receiver_baton;
  plrwb->receiver = receiver;

  *receiver2_baton = plrwb;
  *receiver2 = proplist_wrapper_receiver;
}