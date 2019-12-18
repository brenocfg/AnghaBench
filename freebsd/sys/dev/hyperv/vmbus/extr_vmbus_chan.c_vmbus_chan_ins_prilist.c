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
struct vmbus_softc {int /*<<< orphan*/  vmbus_prichans; int /*<<< orphan*/  vmbus_prichan_lock; } ;
struct vmbus_channel {int /*<<< orphan*/  ch_stflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMBUS_CHAN_ST_ONPRIL_SHIFT ; 
 scalar_t__ atomic_testandset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ch_prilink ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
vmbus_chan_ins_prilist(struct vmbus_softc *sc, struct vmbus_channel *chan)
{

	mtx_assert(&sc->vmbus_prichan_lock, MA_OWNED);
	if (atomic_testandset_int(&chan->ch_stflags,
	    VMBUS_CHAN_ST_ONPRIL_SHIFT))
		panic("channel is already on the prilist");
	TAILQ_INSERT_TAIL(&sc->vmbus_prichans, chan, ch_prilink);
}