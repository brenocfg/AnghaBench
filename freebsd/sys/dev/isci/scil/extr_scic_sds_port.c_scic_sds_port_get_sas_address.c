#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_8__ {int /*<<< orphan*/ ** phy_table; } ;
struct TYPE_7__ {scalar_t__ low; scalar_t__ high; } ;
typedef  TYPE_1__ SCI_SAS_ADDRESS_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_phy_get_sas_address (int /*<<< orphan*/ *,TYPE_1__*) ; 

void scic_sds_port_get_sas_address(
   SCIC_SDS_PORT_T   * this_port,
   SCI_SAS_ADDRESS_T * sas_address
)
{
   U32 index;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_port),
      SCIC_LOG_OBJECT_PORT,
      "scic_sds_port_get_sas_address(0x%x, 0x%x) enter\n",
      this_port, sas_address
   ));

   sas_address->high = 0;
   sas_address->low  = 0;

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      if (this_port->phy_table[index] != NULL)
      {
         scic_sds_phy_get_sas_address(this_port->phy_table[index], sas_address);
      }
   }
}