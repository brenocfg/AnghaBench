#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * timer; } ;
struct TYPE_5__ {TYPE_1__ operation; } ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_cb_timer_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void scif_sas_domain_release_resource(
   SCIF_SAS_CONTROLLER_T * fw_controller,
   SCIF_SAS_DOMAIN_T     * fw_domain
)
{
   if (fw_domain->operation.timer != NULL)
   {
      scif_cb_timer_destroy(fw_controller, fw_domain->operation.timer);
      fw_domain->operation.timer = NULL;
   }
}