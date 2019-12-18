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
struct ess_info {int /*<<< orphan*/  io; int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ess_dmatrigger(struct ess_info *sc, int ch, int go)
{
	KASSERT(ch == 1 || ch == 2, ("bad ch"));
	if (ch == 1)
		port_wr(sc->vc, 0xf, go? 0x00 : 0x01, 1); /* mask */
	else if (ch == 2)
		port_wr(sc->io, 0x6, 0x08 | (go? 0x02 : 0x00), 1); /* autoinit */
	return 0;
}