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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATU_STATS ; 
 int ATU_STATS_BIN ; 
 int ATU_STATS_FLAG ; 
 int /*<<< orphan*/  REG_GLOBAL2 ; 
 int /*<<< orphan*/  e6000sw_readreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_writereg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
e6000sw_set_atustat(device_t dev, e6000sw_softc_t *sc, int bin, int flag)
{
	uint16_t ret;

	ret = e6000sw_readreg(sc, REG_GLOBAL2, ATU_STATS);
	e6000sw_writereg(sc, REG_GLOBAL2, ATU_STATS, (bin << ATU_STATS_BIN ) |
	    (flag << ATU_STATS_FLAG));
}