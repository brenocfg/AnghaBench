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
struct mbuf {int dummy; } ;
struct iwn_softc {int /*<<< orphan*/  sc_xmit_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_LOCK_ASSERT (struct iwn_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static int
iwn_xmit_queue_enqueue(struct iwn_softc *sc, struct mbuf *m)
{

	IWN_LOCK_ASSERT(sc);
	return (mbufq_enqueue(&sc->sc_xmit_queue, m));
}