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
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_sas_controller_execute_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_failed_reset_handler(
   SCI_BASE_CONTROLLER_T * controller
)
{
   return scif_sas_controller_execute_reset((SCIF_SAS_CONTROLLER_T*)controller);
}