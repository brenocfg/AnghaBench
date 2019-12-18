#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_6__ {int /*<<< orphan*/  get; } ;
struct TYPE_5__ {TYPE_2__ uf_control; } ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_UFQGP_WRITE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ scic_sds_unsolicited_frame_control_release_frame (TYPE_2__*,int /*<<< orphan*/ ) ; 

void scic_sds_controller_release_frame(
   SCIC_SDS_CONTROLLER_T *this_controller,
   U32                    frame_index
)
{
   if (scic_sds_unsolicited_frame_control_release_frame(
          &this_controller->uf_control, frame_index) == TRUE)
      SCU_UFQGP_WRITE(this_controller, this_controller->uf_control.get);
}