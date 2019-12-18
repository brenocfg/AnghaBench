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
struct mrsas_softc {scalar_t__ msix_vectors; int reply_q_depth; TYPE_1__* reply_desc_mem; scalar_t__* last_reply_idx; } ;
typedef  TYPE_1__* pMpi2ReplyDescriptorsUnion_t ;
struct TYPE_2__ {int /*<<< orphan*/  Words; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRSAS_ULONG_MAX ; 

void
mrsas_reset_reply_desc(struct mrsas_softc *sc)
{
	int i, count;
	pMpi2ReplyDescriptorsUnion_t reply_desc;

	count = sc->msix_vectors > 0 ? sc->msix_vectors : 1;
	for (i = 0; i < count; i++)
		sc->last_reply_idx[i] = 0;

	reply_desc = sc->reply_desc_mem;
	for (i = 0; i < sc->reply_q_depth; i++, reply_desc++) {
		reply_desc->Words = MRSAS_ULONG_MAX;
	}
}