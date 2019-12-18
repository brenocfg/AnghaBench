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
 int /*<<< orphan*/  AR8216_ATU_ACTIVE ; 
 int /*<<< orphan*/  AR8216_REG_ATU ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int arswitch_waitreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar8xxx_atu_wait_ready(struct arswitch_softc *sc)
{
	int ret;

	ARSWITCH_LOCK_ASSERT(sc, MA_OWNED);

	ret = arswitch_waitreg(sc->sc_dev,
	    AR8216_REG_ATU,
	    AR8216_ATU_ACTIVE,
	    0,
	    1000);

	return (ret);
}