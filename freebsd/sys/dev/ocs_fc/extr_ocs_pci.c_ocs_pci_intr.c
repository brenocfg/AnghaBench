#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocs_softc {int /*<<< orphan*/  sim_lock; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  vec; struct ocs_softc* softc; } ;
typedef  TYPE_1__ ocs_intr_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_OS_MAX_ISR_TIME_MSEC ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_hw_process (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_pci_intr(void *context)
{
	ocs_intr_ctx_t	*intr = context;
	struct ocs_softc *ocs = intr->softc;

	mtx_lock(&ocs->sim_lock);
		ocs_hw_process(&ocs->hw, intr->vec, OCS_OS_MAX_ISR_TIME_MSEC);
	mtx_unlock(&ocs->sim_lock);
}