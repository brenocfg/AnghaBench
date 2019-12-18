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
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_DOMAIN_STATE_INITIAL ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_domain_state_handler_table ; 

__attribute__((used)) static
void scif_sas_domain_initial_state_enter(
   SCI_BASE_OBJECT_T * object
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T *)object;

   SET_STATE_HANDLER(
      fw_domain,
      scif_sas_domain_state_handler_table,
      SCI_BASE_DOMAIN_STATE_INITIAL
   );

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN,
      "scif_sas_domain_initial_state_enter(0x%x) enter\n",
      fw_domain
   ));
}