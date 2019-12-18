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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;
struct atiixp_info {scalar_t__ polling; TYPE_1__ rch; TYPE_1__ pch; int /*<<< orphan*/  poll_timer; } ;

/* Variables and functions */
 scalar_t__ atiixp_chan_active (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_lock (struct atiixp_info*) ; 
 scalar_t__ atiixp_poll_channel (TYPE_1__*) ; 
 int /*<<< orphan*/  atiixp_unlock (struct atiixp_info*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct atiixp_info*) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atiixp_poll_callback(void *arg)
{
	struct atiixp_info *sc = arg;
	uint32_t trigger = 0;

	if (sc == NULL)
		return;

	atiixp_lock(sc);
	if (sc->polling == 0 || atiixp_chan_active(sc) == 0) {
		atiixp_unlock(sc);
		return;
	}

	trigger |= (atiixp_poll_channel(&sc->pch) != 0) ? 1 : 0;
	trigger |= (atiixp_poll_channel(&sc->rch) != 0) ? 2 : 0;

	/* XXX */
	callout_reset(&sc->poll_timer, 1/*sc->poll_ticks*/,
	    atiixp_poll_callback, sc);

	atiixp_unlock(sc);

	if (trigger & 1)
		chn_intr(sc->pch.channel);
	if (trigger & 2)
		chn_intr(sc->rch.channel);
}