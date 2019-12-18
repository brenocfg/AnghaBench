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
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_PORT_STATE_RESETTING ; 
 int /*<<< orphan*/  scic_sds_port_set_base_state_handlers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_port_resetting_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port;
   this_port = (SCIC_SDS_PORT_T *)object;

   scic_sds_port_set_base_state_handlers(
      this_port, SCI_BASE_PORT_STATE_RESETTING
   );
}