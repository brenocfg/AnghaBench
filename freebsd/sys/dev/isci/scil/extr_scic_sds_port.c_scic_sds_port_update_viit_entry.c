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
struct TYPE_8__ {unsigned long physical_port_index; } ;
struct TYPE_7__ {unsigned long high; unsigned long low; } ;
typedef  TYPE_1__ SCI_SAS_ADDRESS_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 unsigned long SCU_VIIT_ENTRY_ID_VIIT ; 
 unsigned long SCU_VIIT_ENTRY_LPVIE_SHIFT ; 
 unsigned long SCU_VIIT_IPPT_INITIATOR ; 
 unsigned long SCU_VIIT_STATUS_ALL_VALID ; 
 int /*<<< orphan*/  initiator_sas_address_hi ; 
 int /*<<< orphan*/  initiator_sas_address_lo ; 
 int /*<<< orphan*/  reserved ; 
 int /*<<< orphan*/  scic_sds_port_get_sas_address (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  scu_port_viit_register_write (TYPE_2__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  status ; 

void scic_sds_port_update_viit_entry(
   SCIC_SDS_PORT_T *this_port
)
{
   SCI_SAS_ADDRESS_T sas_address;

   scic_sds_port_get_sas_address(this_port, &sas_address);

   scu_port_viit_register_write(
      this_port, initiator_sas_address_hi, sas_address.high);

   scu_port_viit_register_write(
      this_port, initiator_sas_address_lo, sas_address.low);

   // This value get cleared just in case its not already cleared
   scu_port_viit_register_write(
      this_port, reserved, 0);


   // We are required to update the status register last
   scu_port_viit_register_write(
      this_port, status, (
           SCU_VIIT_ENTRY_ID_VIIT
         | SCU_VIIT_IPPT_INITIATOR
         | ((1UL << this_port->physical_port_index) << SCU_VIIT_ENTRY_LPVIE_SHIFT)
         | SCU_VIIT_STATUS_ALL_VALID
         )
   );
}