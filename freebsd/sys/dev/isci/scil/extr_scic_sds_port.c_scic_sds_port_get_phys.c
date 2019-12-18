#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_4__ {int /*<<< orphan*/ ** phy_table; } ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 

U32 scic_sds_port_get_phys(
   SCIC_SDS_PORT_T * this_port
)
{
   U32 index;
   U32 mask;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_port),
      SCIC_LOG_OBJECT_PORT,
      "scic_sds_port_get_phys(0x%x) enter\n",
      this_port
   ));

   mask = 0;

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      if (this_port->phy_table[index] != NULL)
      {
         mask |= (1 << index);
      }
   }

   return mask;
}