#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifq_mtx; } ;
struct sppp {int /*<<< orphan*/  mtx; TYPE_2__ pp_fastq; TYPE_1__ pp_cpq; int /*<<< orphan*/  pap_my_to_ch; int /*<<< orphan*/ * ch; int /*<<< orphan*/  keepalive_callout; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int IDX_COUNT ; 
 struct sppp* IFP2SP (struct ifnet*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 

void
sppp_detach(struct ifnet *ifp)
{
	struct sppp *sp = IFP2SP(ifp);
	int i;

	KASSERT(mtx_initialized(&sp->mtx), ("sppp mutex is not initialized"));

	/* Stop keepalive handler. */
 	callout_drain(&sp->keepalive_callout);

	for (i = 0; i < IDX_COUNT; i++) {
		callout_drain(&sp->ch[i]);
	}
	callout_drain(&sp->pap_my_to_ch);

	mtx_destroy(&sp->pp_cpq.ifq_mtx);
	mtx_destroy(&sp->pp_fastq.ifq_mtx);
	mtx_destroy(&sp->mtx);
}