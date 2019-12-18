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
 int /*<<< orphan*/  ENVY24_MT_PCTL ; 
 int ENVY24_MT_PCTL_PSTART ; 
 int ENVY24_MT_PCTL_RSTART ; 
 int PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int envy24_rdmt (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24_wrmt (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
envy24_stop(struct sc_info *sc, int dir)
{
	u_int32_t stat, sw;

#if(0)
	device_printf(sc->dev, "envy24_stop(sc, %d)\n", dir);
#endif
	if (dir == PCMDIR_PLAY)
		sw = ~ENVY24_MT_PCTL_PSTART;
	else
		sw = ~ENVY24_MT_PCTL_RSTART;

	stat = envy24_rdmt(sc, ENVY24_MT_PCTL, 1);
	envy24_wrmt(sc, ENVY24_MT_PCTL, stat & sw, 1);

	return;
}