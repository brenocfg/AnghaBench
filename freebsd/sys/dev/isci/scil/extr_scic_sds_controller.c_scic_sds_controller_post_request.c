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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_INFO (int /*<<< orphan*/ ) ; 
 int SCIC_LOG_OBJECT_COMPLETION_QUEUE ; 
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SMU_PCP_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 

void scic_sds_controller_post_request(
   SCIC_SDS_CONTROLLER_T *this_controller,
   U32                    request
)
{
   SCIC_LOG_INFO((
      sci_base_object_get_logger(this_controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_COMPLETION_QUEUE,
      "SCIC Controller 0x%08x post request 0x%08x\n",
      this_controller, request
   ));

   SMU_PCP_WRITE(this_controller, request);
}