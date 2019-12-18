#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pend_frames_lock; int /*<<< orphan*/  pend_frames; } ;
typedef  TYPE_2__ ocs_xport_fcfi_t ;
struct TYPE_9__ {TYPE_1__* xport; } ;
typedef  TYPE_3__ ocs_t ;
struct TYPE_10__ {size_t fcf_indicator; TYPE_3__* ocs; } ;
typedef  TYPE_4__ ocs_domain_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {TYPE_2__* fcfi; } ;

/* Variables and functions */
 size_t SLI4_MAX_FCFI ; 
 int /*<<< orphan*/  ocs_assert (int,int) ; 
 int /*<<< orphan*/  ocs_purge_pending (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t
ocs_domain_purge_pending(ocs_domain_t *domain)
{
	ocs_t *ocs = domain->ocs;
	ocs_xport_fcfi_t *xport_fcfi;

	ocs_assert(domain->fcf_indicator < SLI4_MAX_FCFI, -1);
	xport_fcfi = &ocs->xport->fcfi[domain->fcf_indicator];
	return ocs_purge_pending(domain->ocs,
				 &xport_fcfi->pend_frames,
				 &xport_fcfi->pend_frames_lock);
}