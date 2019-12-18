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
struct TYPE_4__ {int /*<<< orphan*/ * timer_handle; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_cb_timer_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_cb_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_destroy_dummy_resources (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_get_controller (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_port_stopping_state_exit(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port;
   this_port = (SCIC_SDS_PORT_T *)object;

   scic_cb_timer_stop(
      scic_sds_port_get_controller(this_port),
      this_port->timer_handle
   );

   scic_cb_timer_destroy(
      scic_sds_port_get_controller(this_port),
      this_port->timer_handle
   );
   this_port->timer_handle = NULL;

   scic_sds_port_destroy_dummy_resources(this_port);
}