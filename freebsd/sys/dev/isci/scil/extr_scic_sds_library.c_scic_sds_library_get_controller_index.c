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
typedef  size_t U8 ;
struct TYPE_3__ {size_t max_controller_count; int /*<<< orphan*/ * controllers; } ;
typedef  TYPE_1__ SCIC_SDS_LIBRARY_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */

U8 scic_sds_library_get_controller_index(
   SCIC_SDS_LIBRARY_T    * library,
   SCIC_SDS_CONTROLLER_T * controller
)
{
   U8 index;

   for (index = 0; index < library->max_controller_count; index++)
   {
      if (controller == &library->controllers[index])
      {
         return index;
      }
   }

   return 0xff;
}