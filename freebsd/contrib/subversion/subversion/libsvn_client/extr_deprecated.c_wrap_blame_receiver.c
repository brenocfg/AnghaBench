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
typedef  int /*<<< orphan*/  svn_client_blame_receiver_t ;
typedef  int /*<<< orphan*/  svn_client_blame_receiver2_t ;
struct blame_receiver_wrapper_baton {int /*<<< orphan*/  receiver; void* baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct blame_receiver_wrapper_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blame_wrapper_receiver ; 

__attribute__((used)) static void
wrap_blame_receiver(svn_client_blame_receiver2_t *receiver2,
                    void **receiver2_baton,
                    svn_client_blame_receiver_t receiver,
                    void *receiver_baton,
                    apr_pool_t *pool)
{
  struct blame_receiver_wrapper_baton *brwb = apr_palloc(pool, sizeof(*brwb));

  /* Set the user provided old format callback in the baton. */
  brwb->baton = receiver_baton;
  brwb->receiver = receiver;

  *receiver2_baton = brwb;
  *receiver2 = blame_wrapper_receiver;
}