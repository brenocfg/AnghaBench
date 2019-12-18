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
 int ENVY24HT_MT_INT_MASK ; 
 int ENVY24HT_MT_INT_PMASK ; 
 int ENVY24HT_MT_INT_PSTAT ; 
 int ENVY24HT_MT_INT_RMASK ; 
 int ENVY24HT_MT_INT_RSTAT ; 
 int ENVY24HT_MT_INT_STAT ; 
 int PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int envy24ht_rdmt (struct sc_info*,int,int) ; 
 int /*<<< orphan*/  envy24ht_wrmt (struct sc_info*,int,int,int) ; 

__attribute__((used)) static int
envy24ht_checkintr(struct sc_info *sc, int dir)
{
	u_int32_t mask, stat, intr, rtn;

#if(0)
	device_printf(sc->dev, "envy24ht_checkintr(sc, %d)\n", dir);
#endif
	intr = envy24ht_rdmt(sc, ENVY24HT_MT_INT_STAT, 1);
	if (dir == PCMDIR_PLAY) {
		if ((rtn = intr & ENVY24HT_MT_INT_PSTAT) != 0) {
			mask = ~ENVY24HT_MT_INT_RSTAT;
			envy24ht_wrmt(sc, 0x1a, 0x01, 1);
			envy24ht_wrmt(sc, ENVY24HT_MT_INT_STAT, (intr & mask) | ENVY24HT_MT_INT_PSTAT | 0x08, 1);	
			stat = envy24ht_rdmt(sc, ENVY24HT_MT_INT_MASK, 1);
			envy24ht_wrmt(sc, ENVY24HT_MT_INT_MASK, stat | ENVY24HT_MT_INT_PMASK, 1);
		}
	}
	else {
		if ((rtn = intr & ENVY24HT_MT_INT_RSTAT) != 0) {
			mask = ~ENVY24HT_MT_INT_PSTAT;
#if 0
			stat = ENVY24HT_MT_INT_RSTAT | ENVY24HT_MT_INT_RMASK;
#endif
			envy24ht_wrmt(sc, ENVY24HT_MT_INT_STAT, (intr & mask) | ENVY24HT_MT_INT_RSTAT, 1);
			stat = envy24ht_rdmt(sc, ENVY24HT_MT_INT_MASK, 1);
			envy24ht_wrmt(sc, ENVY24HT_MT_INT_MASK, stat | ENVY24HT_MT_INT_RMASK, 1);
		}
	}

	return rtn;
}