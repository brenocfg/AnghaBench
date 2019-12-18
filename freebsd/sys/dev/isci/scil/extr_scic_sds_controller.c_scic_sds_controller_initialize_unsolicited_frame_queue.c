#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_8__ {int /*<<< orphan*/  count; } ;
struct TYPE_9__ {TYPE_1__ address_table; } ;
struct TYPE_10__ {TYPE_2__ uf_control; } ;
typedef  TYPE_3__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_BIT ; 
 int /*<<< orphan*/  POINTER ; 
 int /*<<< orphan*/  QUEUE_SIZE ; 
 int SCU_UFQC_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_UFQC_WRITE (TYPE_3__*,int) ; 
 int SCU_UFQGP_GEN_BIT (int /*<<< orphan*/ ) ; 
 int SCU_UFQGP_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_UFQGP_WRITE (TYPE_3__*,int) ; 
 int SCU_UFQPP_GEN_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_UFQPP_WRITE (TYPE_3__*,int) ; 

void scic_sds_controller_initialize_unsolicited_frame_queue(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   U32 frame_queue_control_value;
   U32 frame_queue_get_value;
   U32 frame_queue_put_value;

   // Write the queue size
   frame_queue_control_value =
      SCU_UFQC_GEN_VAL(QUEUE_SIZE, this_controller->uf_control.address_table.count);

   SCU_UFQC_WRITE(this_controller, frame_queue_control_value);

   // Setup the get pointer for the unsolicited frame queue
   frame_queue_get_value = (
         SCU_UFQGP_GEN_VAL(POINTER, 0)
      |  SCU_UFQGP_GEN_BIT(ENABLE_BIT)
      );

   SCU_UFQGP_WRITE(this_controller, frame_queue_get_value);

   // Setup the put pointer for the unsolicited frame queue
   frame_queue_put_value = SCU_UFQPP_GEN_VAL(POINTER, 0);

   SCU_UFQPP_WRITE(this_controller, frame_queue_put_value);
}