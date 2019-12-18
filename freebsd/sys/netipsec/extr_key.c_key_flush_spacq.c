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
typedef  scalar_t__ time_t ;
struct secspacq {scalar_t__ created; } ;

/* Variables and functions */
 struct secspacq* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct secspacq* LIST_NEXT (struct secspacq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct secspacq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPSEC_SAQ ; 
 int /*<<< orphan*/  SPACQ_LOCK () ; 
 int /*<<< orphan*/  SPACQ_UNLOCK () ; 
 scalar_t__ V_key_blockacq_lifetime ; 
 int /*<<< orphan*/  V_spacqtree ; 
 scalar_t__ __LIST_CHAINED (struct secspacq*) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  free (struct secspacq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
key_flush_spacq(time_t now)
{
	struct secspacq *acq, *nextacq;

	/* SP ACQ tree */
	SPACQ_LOCK();
	for (acq = LIST_FIRST(&V_spacqtree); acq != NULL; acq = nextacq) {
		nextacq = LIST_NEXT(acq, chain);
		if (now - acq->created > V_key_blockacq_lifetime
		 && __LIST_CHAINED(acq)) {
			LIST_REMOVE(acq, chain);
			free(acq, M_IPSEC_SAQ);
		}
	}
	SPACQ_UNLOCK();
}