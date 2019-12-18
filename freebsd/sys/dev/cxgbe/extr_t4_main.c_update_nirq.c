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
struct intrs_and_queues {int nirq; int nrxq; int nofldrxq; int num_vis; int nofldrxq_vi; int /*<<< orphan*/  nnmrxq_vi; int /*<<< orphan*/  nrxq_vi; } ;

/* Variables and functions */
 int T4_EXTRA_INTR ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_nirq(struct intrs_and_queues *iaq, int nports)
{
	int extra = T4_EXTRA_INTR;

	iaq->nirq = extra;
	iaq->nirq += nports * (iaq->nrxq + iaq->nofldrxq);
	iaq->nirq += nports * (iaq->num_vis - 1) *
	    max(iaq->nrxq_vi, iaq->nnmrxq_vi);
	iaq->nirq += nports * (iaq->num_vis - 1) * iaq->nofldrxq_vi;
}