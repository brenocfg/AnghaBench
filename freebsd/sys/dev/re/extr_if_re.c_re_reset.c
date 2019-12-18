#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rl_softc {int rl_flags; int /*<<< orphan*/  rl_dev; TYPE_1__* rl_hwrev; } ;
struct TYPE_2__ {scalar_t__ rl_rev; } ;

/* Variables and functions */
 int CSR_READ_1 (struct rl_softc*,int) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int RL_CMD_RESET ; 
 int RL_COMMAND ; 
 int RL_FLAG_MACRESET ; 
 scalar_t__ RL_HWREV_8169S ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int RL_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  re_gmii_writereg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
re_reset(struct rl_softc *sc)
{
	int			i;

	RL_LOCK_ASSERT(sc);

	CSR_WRITE_1(sc, RL_COMMAND, RL_CMD_RESET);

	for (i = 0; i < RL_TIMEOUT; i++) {
		DELAY(10);
		if (!(CSR_READ_1(sc, RL_COMMAND) & RL_CMD_RESET))
			break;
	}
	if (i == RL_TIMEOUT)
		device_printf(sc->rl_dev, "reset never completed!\n");

	if ((sc->rl_flags & RL_FLAG_MACRESET) != 0)
		CSR_WRITE_1(sc, 0x82, 1);
	if (sc->rl_hwrev->rl_rev == RL_HWREV_8169S)
		re_gmii_writereg(sc->rl_dev, 1, 0x0b, 0);
}