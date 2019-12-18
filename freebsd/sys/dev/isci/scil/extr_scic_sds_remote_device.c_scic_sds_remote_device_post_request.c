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
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_sds_controller_post_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_build_command_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_controller (int /*<<< orphan*/ *) ; 

void scic_sds_remote_device_post_request(
   SCIC_SDS_REMOTE_DEVICE_T * this_device,
   U32                        request
)
{
   U32 context;

   context = scic_sds_remote_device_build_command_context(this_device, request);

   scic_sds_controller_post_request(
      scic_sds_remote_device_get_controller(this_device),
      context
   );
}