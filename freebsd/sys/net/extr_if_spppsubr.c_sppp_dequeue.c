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
struct sppp {scalar_t__ pp_mode; int /*<<< orphan*/  pp_fastq; int /*<<< orphan*/  pp_cpq; } ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 scalar_t__ IFF_CISCO ; 
 struct sppp* IFP2SP (struct ifnet*) ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ PP_FR ; 
 TYPE_1__* SP2IFP (struct sppp*) ; 
 int /*<<< orphan*/  SPPP_LOCK (struct sppp*) ; 
 int /*<<< orphan*/  SPPP_UNLOCK (struct sppp*) ; 
 scalar_t__ sppp_ncp_check (struct sppp*) ; 

struct mbuf *
sppp_dequeue(struct ifnet *ifp)
{
	struct sppp *sp = IFP2SP(ifp);
	struct mbuf *m;

	SPPP_LOCK(sp);
	/*
	 * Process only the control protocol queue until we have at
	 * least one NCP open.
	 *
	 * Do always serve all three queues in Cisco mode.
	 */
	IF_DEQUEUE(&sp->pp_cpq, m);
	if (m == NULL &&
	    (sppp_ncp_check(sp) || sp->pp_mode == IFF_CISCO ||
	     sp->pp_mode == PP_FR)) {
		IF_DEQUEUE(&sp->pp_fastq, m);
		if (m == NULL)
			IF_DEQUEUE (&SP2IFP(sp)->if_snd, m);
	}
	SPPP_UNLOCK(sp);
	return m;
}