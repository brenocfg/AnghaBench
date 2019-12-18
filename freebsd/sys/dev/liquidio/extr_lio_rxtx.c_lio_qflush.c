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
struct TYPE_2__ {int iq; } ;
struct octeon_device {struct lio_instr_queue** instr_queue; TYPE_1__ io_qmask; } ;
struct mbuf {int dummy; } ;
struct lio_instr_queue {int /*<<< orphan*/  enq_lock; int /*<<< orphan*/  br; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int LIO_MAX_INSTR_QUEUES (struct octeon_device*) ; 
 struct mbuf* buf_ring_dequeue_sc (int /*<<< orphan*/ ) ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  if_qflush (struct ifnet*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
lio_qflush(struct ifnet *ifp)
{
	struct lio		*lio = if_getsoftc(ifp);
	struct octeon_device	*oct = lio->oct_dev;
	struct lio_instr_queue	*iq;
	struct mbuf		*m;
	int	i;

	for (i = 0; i < LIO_MAX_INSTR_QUEUES(oct); i++) {
		if (!(oct->io_qmask.iq & BIT_ULL(i)))
			continue;

		iq = oct->instr_queue[i];

		mtx_lock(&iq->enq_lock);
		while ((m = buf_ring_dequeue_sc(iq->br)) != NULL)
			m_freem(m);

		mtx_unlock(&iq->enq_lock);
	}

	if_qflush(ifp);
}