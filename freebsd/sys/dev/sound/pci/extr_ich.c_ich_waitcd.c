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
struct sc_info {int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int ICH_IGNORE_PCR ; 
 int /*<<< orphan*/  ICH_REG_ACC_SEMA ; 
 int ICH_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ich_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ich_waitcd(void *devinfo)
{
	struct sc_info *sc = (struct sc_info *)devinfo;
	uint32_t data;
	int i;

	for (i = 0; i < ICH_TIMEOUT; i++) {
		data = ich_rd(sc, ICH_REG_ACC_SEMA, 1);
		if ((data & 0x01) == 0)
			return (0);
		DELAY(1);
	}
	if ((sc->flags & ICH_IGNORE_PCR) != 0)
		return (0);
	device_printf(sc->dev, "CODEC semaphore timeout\n");
	return (ETIMEDOUT);
}