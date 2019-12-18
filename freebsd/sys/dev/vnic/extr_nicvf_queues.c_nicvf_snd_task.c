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
struct snd_queue {int /*<<< orphan*/  snd_task; int /*<<< orphan*/  snd_taskq; struct nicvf* nic; } ;
struct nicvf {int /*<<< orphan*/  link_up; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  NICVF_TX_LOCK (struct snd_queue*) ; 
 int /*<<< orphan*/  NICVF_TX_UNLOCK (struct snd_queue*) ; 
 int if_getdrvflags (struct ifnet*) ; 
 int nicvf_xmit_locked (struct snd_queue*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nicvf_snd_task(void *arg, int pending)
{
	struct snd_queue *sq = (struct snd_queue *)arg;
	struct nicvf *nic;
	struct ifnet *ifp;
	int err;

	nic = sq->nic;
	ifp = nic->ifp;

	/*
	 * Skip sending anything if the driver is not running,
	 * SQ full or link is down.
	 */
	if (((if_getdrvflags(ifp) & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING) || !nic->link_up)
		return;

	NICVF_TX_LOCK(sq);
	err = nicvf_xmit_locked(sq);
	NICVF_TX_UNLOCK(sq);
	/* Try again */
	if (err != 0)
		taskqueue_enqueue(sq->snd_taskq, &sq->snd_task);
}