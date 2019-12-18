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
struct sc_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24_MT_INT ; 
 int ENVY24_MT_INT_PMASK ; 
 int ENVY24_MT_INT_PSTAT ; 
 int ENVY24_MT_INT_RMASK ; 
 int ENVY24_MT_INT_RSTAT ; 
 int PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int envy24_rdmt (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24_wrmt (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
envy24_checkintr(struct sc_info *sc, int dir)
{
	u_int32_t mask, stat, intr, rtn;

#if(0)
	device_printf(sc->dev, "envy24_checkintr(sc, %d)\n", dir);
#endif
	intr = envy24_rdmt(sc, ENVY24_MT_INT, 1);
	if (dir == PCMDIR_PLAY) {
		if ((rtn = intr & ENVY24_MT_INT_PSTAT) != 0) {
			mask = ~ENVY24_MT_INT_RSTAT;
			stat = ENVY24_MT_INT_PSTAT | ENVY24_MT_INT_PMASK;
			envy24_wrmt(sc, ENVY24_MT_INT, (intr & mask) | stat, 1);
		}
	}
	else {
		if ((rtn = intr & ENVY24_MT_INT_RSTAT) != 0) {
			mask = ~ENVY24_MT_INT_PSTAT;
			stat = ENVY24_MT_INT_RSTAT | ENVY24_MT_INT_RMASK;
			envy24_wrmt(sc, ENVY24_MT_INT, (intr & mask) | stat, 1);
		}
	}

	return rtn;
}