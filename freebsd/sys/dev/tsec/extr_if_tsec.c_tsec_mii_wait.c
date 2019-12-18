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
struct tsec_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int TSEC_PHY_READ (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSEC_READ_DELAY ; 
 int TSEC_READ_RETRY ; 
 int /*<<< orphan*/  TSEC_REG_MIIMIND ; 

__attribute__((used)) static int
tsec_mii_wait(struct tsec_softc *sc, uint32_t flags)
{
	int timeout;

	/*
	 * The status indicators are not set immediatly after a command.
	 * Discard the first value.
	 */
	TSEC_PHY_READ(sc, TSEC_REG_MIIMIND);

	timeout = TSEC_READ_RETRY;
	while ((TSEC_PHY_READ(sc, TSEC_REG_MIIMIND) & flags) && --timeout)
		DELAY(TSEC_READ_DELAY);

	return (timeout == 0);
}