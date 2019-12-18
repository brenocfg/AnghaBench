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
 int /*<<< orphan*/  ENVY24HT_CCS_I2CDEV_ROM ; 
 int /*<<< orphan*/  ENVY24HT_CCS_I2CSTAT ; 
 int ENVY24HT_CCS_I2CSTAT_ROM ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int envy24ht_rdcs (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int envy24ht_rdi2c (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
envy24ht_rdrom(struct sc_info *sc, u_int32_t addr)
{
	u_int32_t data;

#if(0)
	device_printf(sc->dev, "envy24ht_rdrom(sc, 0x%02x)\n", addr);
#endif
	data = envy24ht_rdcs(sc, ENVY24HT_CCS_I2CSTAT, 1);
	if ((data & ENVY24HT_CCS_I2CSTAT_ROM) == 0) {
#if(0)
		device_printf(sc->dev, "envy24ht_rdrom(): E2PROM not presented\n");
#endif
		return -1;
	}

	return envy24ht_rdi2c(sc, ENVY24HT_CCS_I2CDEV_ROM, addr);
}