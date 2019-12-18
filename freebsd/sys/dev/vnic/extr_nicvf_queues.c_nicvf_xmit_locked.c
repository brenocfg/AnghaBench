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
struct snd_queue {int /*<<< orphan*/  br; struct nicvf* nic; } ;
struct nicvf {struct ifnet* ifp; } ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  NICVF_TX_LOCK_ASSERT (struct snd_queue*) ; 
 int /*<<< orphan*/  drbr_advance (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct mbuf* drbr_peek (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbr_putback (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int nicvf_tx_mbuf_locked (struct snd_queue*,struct mbuf**) ; 

int
nicvf_xmit_locked(struct snd_queue *sq)
{
	struct nicvf *nic;
	struct ifnet *ifp;
	struct mbuf *next;
	int err;

	NICVF_TX_LOCK_ASSERT(sq);

	nic = sq->nic;
	ifp = nic->ifp;
	err = 0;

	while ((next = drbr_peek(ifp, sq->br)) != NULL) {
		/* Send a copy of the frame to the BPF listener */
		ETHER_BPF_MTAP(ifp, next);

		err = nicvf_tx_mbuf_locked(sq, &next);
		if (err != 0) {
			if (next == NULL)
				drbr_advance(ifp, sq->br);
			else
				drbr_putback(ifp, sq->br, next);

			break;
		}
		drbr_advance(ifp, sq->br);
	}
	return (err);
}