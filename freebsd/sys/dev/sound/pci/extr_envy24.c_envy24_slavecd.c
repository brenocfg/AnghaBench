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
 int /*<<< orphan*/  ENVY24_MT_AC97CMD ; 
 int ENVY24_MT_AC97CMD_CLD ; 
 int ENVY24_MT_AC97CMD_RDY ; 
 int ENVY24_MT_AC97CMD_WRM ; 
 int ENVY24_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int envy24_rdmt (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24_wrmt (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
envy24_slavecd(struct sc_info *sc)
{
	u_int32_t data;
	int i;

#if(0)
	device_printf(sc->dev, "envy24_slavecd()\n");
#endif
	envy24_wrmt(sc, ENVY24_MT_AC97CMD,
	    ENVY24_MT_AC97CMD_CLD | ENVY24_MT_AC97CMD_WRM, 1);
	DELAY(10);
	envy24_wrmt(sc, ENVY24_MT_AC97CMD, 0, 1);
	DELAY(1000);
	for (i = 0; i < ENVY24_TIMEOUT; i++) {
		data = envy24_rdmt(sc, ENVY24_MT_AC97CMD, 1);
		if (data & ENVY24_MT_AC97CMD_RDY) {
			return 0;
		}
	}

	return -1;
}