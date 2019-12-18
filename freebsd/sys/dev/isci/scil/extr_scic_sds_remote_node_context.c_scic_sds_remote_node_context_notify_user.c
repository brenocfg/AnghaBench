#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * user_cookie; int /*<<< orphan*/  (* user_callback ) (void*) ;} ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;
typedef  int /*<<< orphan*/  (* SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static
void scic_sds_remote_node_context_notify_user(
   SCIC_SDS_REMOTE_NODE_CONTEXT_T *rnc
)
{
   SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK local_user_callback = rnc->user_callback;
   void * local_user_cookie = rnc->user_cookie;

   //we need to set the user_callback to NULL before it is called, because
   //the user callback's stack may eventually also set up a new set of
   //user callback. If we nullify the user_callback after it is called,
   //we are in the risk to lose the freshly set user callback.
   rnc->user_callback = NULL;
   rnc->user_cookie = NULL;

   if (local_user_callback != NULL)
   {
      (*local_user_callback)(local_user_cookie);
   }
}