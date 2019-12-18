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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  drvsm; scalar_t__ flogi_service_params; TYPE_1__ dma; } ;
typedef  TYPE_2__ ocs_domain_t ;
typedef  int /*<<< orphan*/  fc_plogi_payload_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_DOMAIN_REQ_ATTACH ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_sm_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
__ocs_domain_attach_internal(ocs_domain_t *domain, uint32_t s_id)
{
	ocs_memcpy(domain->dma.virt, ((uint8_t*)domain->flogi_service_params)+4, sizeof (fc_plogi_payload_t) - 4);
	(void)ocs_sm_post_event(&domain->drvsm, OCS_EVT_DOMAIN_REQ_ATTACH, &s_id);
}