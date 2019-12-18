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
struct secacq {scalar_t__ created; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQ_LOCK () ; 
 int /*<<< orphan*/  ACQ_UNLOCK () ; 
 struct secacq* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct secacq* LIST_NEXT (struct secacq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct secacq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPSEC_SAQ ; 
 int /*<<< orphan*/  V_acqtree ; 
 scalar_t__ V_key_blockacq_lifetime ; 
 int /*<<< orphan*/  addrhash ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  free (struct secacq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqhash ; 

__attribute__((used)) static void
key_flush_acq(time_t now)
{
	struct secacq *acq, *nextacq;

	/* ACQ tree */
	ACQ_LOCK();
	acq = LIST_FIRST(&V_acqtree);
	while (acq != NULL) {
		nextacq = LIST_NEXT(acq, chain);
		if (now - acq->created > V_key_blockacq_lifetime) {
			LIST_REMOVE(acq, chain);
			LIST_REMOVE(acq, addrhash);
			LIST_REMOVE(acq, seqhash);
			free(acq, M_IPSEC_SAQ);
		}
		acq = nextacq;
	}
	ACQ_UNLOCK();
}