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
typedef  int /*<<< orphan*/  ae_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_PHY_WRITE (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
ae_phy_init(ae_softc_t *sc)
{

	/*
	 * Enable link status change interrupt.
	 * XXX magic numbers.
	 */
#ifdef notyet
	AE_PHY_WRITE(sc, 18, 0xc00);
#endif
}