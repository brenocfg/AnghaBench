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
typedef  int uint32_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int R88E_MACID_NO_LINK ; 
 int /*<<< orphan*/  rtwn_setbits_4 (struct rtwn_softc*,int,int,int) ; 

void
r88e_macid_enable_link(struct rtwn_softc *sc, int id, int enable)
{
	uint32_t reg;

	reg = R88E_MACID_NO_LINK;
	if (id > 32)
		reg += 4;

	if (enable)
		rtwn_setbits_4(sc, reg, 1 << (id % 32), 0);
	else
		rtwn_setbits_4(sc, reg, 0, 1 << (id % 32));

	/* XXX max macid for tx reports */
}