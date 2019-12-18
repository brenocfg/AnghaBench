#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int E6000SW_SMI_TIMEOUT ; 
 int MDIO_READ (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMI_CMD ; 
 int SMI_CMD_BUSY ; 

__attribute__((used)) static int
e6000sw_smi_waitready(e6000sw_softc_t *sc, int phy)
{
	int i;

	for (i = 0; i < E6000SW_SMI_TIMEOUT; i++) {
		if ((MDIO_READ(sc->dev, phy, SMI_CMD) & SMI_CMD_BUSY) == 0)
			return (0);
		DELAY(1);
	}

	return (1);
}