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
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8327_ATU_FUNC_BUSY ; 
 int /*<<< orphan*/  AR8327_REG_ATU_FUNC ; 
 int arswitch_waitreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar8327_atu_wait_ready(struct arswitch_softc *sc)
{
	int ret;

	ret = arswitch_waitreg(sc->sc_dev,
	    AR8327_REG_ATU_FUNC,
	    AR8327_ATU_FUNC_BUSY,
	    0,
	    1000);

	return (ret);
}