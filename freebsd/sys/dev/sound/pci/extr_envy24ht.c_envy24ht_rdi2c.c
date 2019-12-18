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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ENVY24HT_CCS_I2CADDR ; 
 int /*<<< orphan*/  ENVY24HT_CCS_I2CDATA ; 
 int /*<<< orphan*/  ENVY24HT_CCS_I2CDEV ; 
 int ENVY24HT_CCS_I2CDEV_ADDR ; 
 int ENVY24HT_CCS_I2CDEV_RD ; 
 int /*<<< orphan*/  ENVY24HT_CCS_I2CSTAT ; 
 int ENVY24HT_CCS_I2CSTAT_BSY ; 
 int ENVY24HT_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int envy24ht_rdcs (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24ht_wrcs (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
envy24ht_rdi2c(struct sc_info *sc, u_int32_t dev, u_int32_t addr)
{
	u_int32_t data;
	int i;

#if(0)
	device_printf(sc->dev, "envy24ht_rdi2c(sc, 0x%02x, 0x%02x)\n", dev, addr);
#endif
	for (i = 0; i < ENVY24HT_TIMEOUT; i++) {
		data = envy24ht_rdcs(sc, ENVY24HT_CCS_I2CSTAT, 1);
		if ((data & ENVY24HT_CCS_I2CSTAT_BSY) == 0)
			break;
		DELAY(32); /* 31.25kHz */
	}
	if (i == ENVY24HT_TIMEOUT) {
		return -1;
	}
	envy24ht_wrcs(sc, ENVY24HT_CCS_I2CADDR, addr, 1);
	envy24ht_wrcs(sc, ENVY24HT_CCS_I2CDEV,
	    (dev & ENVY24HT_CCS_I2CDEV_ADDR) | ENVY24HT_CCS_I2CDEV_RD, 1);
	for (i = 0; i < ENVY24HT_TIMEOUT; i++) {
		data = envy24ht_rdcs(sc, ENVY24HT_CCS_I2CSTAT, 1);
		if ((data & ENVY24HT_CCS_I2CSTAT_BSY) == 0)
			break;
		DELAY(32); /* 31.25kHz */
	}
	if (i == ENVY24HT_TIMEOUT) {
		return -1;
	}
	data = envy24ht_rdcs(sc, ENVY24HT_CCS_I2CDATA, 1);

#if(0)
	device_printf(sc->dev, "envy24ht_rdi2c(): return 0x%x\n", data);
#endif
	return (int)data;
}