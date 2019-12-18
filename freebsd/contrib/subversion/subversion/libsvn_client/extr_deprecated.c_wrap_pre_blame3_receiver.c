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
struct wrapped_receiver_baton_s {void* orig_baton; int /*<<< orphan*/  orig_receiver; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  APR_EOL_STR ;

/* Variables and functions */
 struct wrapped_receiver_baton_s* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wrapped_receiver ; 

__attribute__((used)) static void
wrap_pre_blame3_receiver(svn_client_blame_receiver_t *receiver,
                         void **receiver_baton,
                         apr_pool_t *pool)
{
  if (sizeof(APR_EOL_STR) == 3)
    {
      struct wrapped_receiver_baton_s *b = apr_palloc(pool,sizeof(*b));

      b->orig_receiver = *receiver;
      b->orig_baton = *receiver_baton;

      *receiver_baton = b;
      *receiver = wrapped_receiver;
    }
}