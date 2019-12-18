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
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct ess_info {int* dmasz; int /*<<< orphan*/  io; int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCMDIR_PLAY ; 
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ess_dmasetup(struct ess_info *sc, int ch, u_int32_t base, u_int16_t cnt, int dir)
{
	KASSERT(ch == 1 || ch == 2, ("bad ch"));
	sc->dmasz[ch - 1] = cnt;
	if (ch == 1) {
		port_wr(sc->vc, 0x8, 0xc4, 1); /* command */
		port_wr(sc->vc, 0xd, 0xff, 1); /* reset */
		port_wr(sc->vc, 0xf, 0x01, 1); /* mask */
		port_wr(sc->vc, 0xb, dir == PCMDIR_PLAY? 0x58 : 0x54, 1); /* mode */
		port_wr(sc->vc, 0x0, base, 4);
		port_wr(sc->vc, 0x4, cnt - 1, 2);

	} else if (ch == 2) {
		port_wr(sc->io, 0x6, 0x08, 1); /* autoinit */
		port_wr(sc->io, 0x0, base, 4);
		port_wr(sc->io, 0x4, cnt, 2);
	}
	return 0;
}