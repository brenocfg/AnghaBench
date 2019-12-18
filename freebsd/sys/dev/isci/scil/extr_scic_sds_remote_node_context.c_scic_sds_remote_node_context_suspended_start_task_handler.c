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
struct SCIC_SDS_REQUEST {int dummy; } ;
struct SCIC_SDS_REMOTE_NODE_CONTEXT {int dummy; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_resume (struct SCIC_SDS_REMOTE_NODE_CONTEXT*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_node_context_suspended_start_task_handler(
   struct SCIC_SDS_REMOTE_NODE_CONTEXT * this_rnc,
   struct SCIC_SDS_REQUEST             * the_request
)
{
   scic_sds_remote_node_context_resume(this_rnc, NULL, NULL);

   return SCI_SUCCESS;
}