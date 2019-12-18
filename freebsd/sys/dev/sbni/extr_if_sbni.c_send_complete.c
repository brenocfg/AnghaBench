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
struct sbni_softc {int /*<<< orphan*/  ifp; int /*<<< orphan*/ * tx_buf_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
send_complete(struct sbni_softc *sc)
{
	m_freem(sc->tx_buf_p);
	sc->tx_buf_p = NULL;
	if_inc_counter(sc->ifp, IFCOUNTER_OPACKETS, 1);
}