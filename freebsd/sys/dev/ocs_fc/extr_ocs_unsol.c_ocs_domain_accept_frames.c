#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int hold_frames; } ;
typedef  TYPE_2__ ocs_xport_fcfi_t ;
struct TYPE_10__ {TYPE_1__* xport; } ;
typedef  TYPE_3__ ocs_t ;
struct TYPE_11__ {size_t fcf_indicator; TYPE_3__* ocs; } ;
typedef  TYPE_4__ ocs_domain_t ;
struct TYPE_8__ {TYPE_2__* fcfi; } ;

/* Variables and functions */
 size_t SLI4_MAX_FCFI ; 
 int /*<<< orphan*/  ocs_assert (int) ; 
 int /*<<< orphan*/  ocs_domain_process_pending (TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_3__*,char*,size_t) ; 

void
ocs_domain_accept_frames(ocs_domain_t *domain)
{
	ocs_t *ocs = domain->ocs;
	ocs_xport_fcfi_t *xport_fcfi;

	ocs_assert(domain->fcf_indicator < SLI4_MAX_FCFI);
	xport_fcfi = &ocs->xport->fcfi[domain->fcf_indicator];
	if (xport_fcfi->hold_frames == 1) {
		ocs_log_debug(domain->ocs, "hold frames cleared for FCFI %d\n",
			      domain->fcf_indicator);
	}
	xport_fcfi->hold_frames = 0;
	ocs_domain_process_pending(domain);
}