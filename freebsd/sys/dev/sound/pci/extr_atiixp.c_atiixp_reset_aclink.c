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
struct atiixp_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_CMD ; 
 int ATI_REG_CMD_ACLINK_ACTIVE ; 
 int ATI_REG_CMD_AC_RESET ; 
 int ATI_REG_CMD_AC_SOFT_RESET ; 
 int ATI_REG_CMD_AC_SYNC ; 
 int ATI_REG_CMD_POWERDOWN ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int atiixp_rd (struct atiixp_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_wr (struct atiixp_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
atiixp_reset_aclink(struct atiixp_info *sc)
{
	uint32_t value, timeout;

	/* if power is down, power it up */
	value = atiixp_rd(sc, ATI_REG_CMD);
	if (value & ATI_REG_CMD_POWERDOWN) {
		/* explicitly enable power */
		value &= ~ATI_REG_CMD_POWERDOWN;
		atiixp_wr(sc, ATI_REG_CMD, value);

		/* have to wait at least 10 usec for it to initialise */
		DELAY(20);
	}

	/* perform a soft reset */
	value  = atiixp_rd(sc, ATI_REG_CMD);
	value |= ATI_REG_CMD_AC_SOFT_RESET;
	atiixp_wr(sc, ATI_REG_CMD, value);

	/* need to read the CMD reg and wait aprox. 10 usec to init */
	value  = atiixp_rd(sc, ATI_REG_CMD);
	DELAY(20);

	/* clear soft reset flag again */
	value  = atiixp_rd(sc, ATI_REG_CMD);
	value &= ~ATI_REG_CMD_AC_SOFT_RESET;
	atiixp_wr(sc, ATI_REG_CMD, value);

	/* check if the ac-link is working; reset device otherwise */
	timeout = 10;
	value = atiixp_rd(sc, ATI_REG_CMD);
	while (!(value & ATI_REG_CMD_ACLINK_ACTIVE) && --timeout) {
#if 0
		device_printf(sc->dev, "not up; resetting aclink hardware\n");
#endif

		/* dip aclink reset but keep the acsync */
		value &= ~ATI_REG_CMD_AC_RESET;
		value |=  ATI_REG_CMD_AC_SYNC;
		atiixp_wr(sc, ATI_REG_CMD, value);

		/* need to read CMD again and wait again (clocking in issue?) */
		value = atiixp_rd(sc, ATI_REG_CMD);
		DELAY(20);

		/* assert aclink reset again */
		value = atiixp_rd(sc, ATI_REG_CMD);
		value |=  ATI_REG_CMD_AC_RESET;
		atiixp_wr(sc, ATI_REG_CMD, value);

		/* check if its active now */
		value = atiixp_rd(sc, ATI_REG_CMD);
	}

	if (timeout == 0)
		device_printf(sc->dev, "giving up aclink reset\n");
#if 0
	if (timeout != 10)
		device_printf(sc->dev, "aclink hardware reset successful\n");
#endif

	/* assert reset and sync for safety */
	value  = atiixp_rd(sc, ATI_REG_CMD);
	value |= ATI_REG_CMD_AC_SYNC | ATI_REG_CMD_AC_RESET;
	atiixp_wr(sc, ATI_REG_CMD, value);
}