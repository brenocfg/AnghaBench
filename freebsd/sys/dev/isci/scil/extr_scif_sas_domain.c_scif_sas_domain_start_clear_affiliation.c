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
typedef  int /*<<< orphan*/  SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_sas_domain_continue_clear_affiliation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_domain_schedule_clear_affiliation (int /*<<< orphan*/ *) ; 

void scif_sas_domain_start_clear_affiliation(
   SCIF_SAS_DOMAIN_T * fw_domain
)
{
   scif_sas_domain_schedule_clear_affiliation(fw_domain);
   scif_sas_domain_continue_clear_affiliation(fw_domain);
}