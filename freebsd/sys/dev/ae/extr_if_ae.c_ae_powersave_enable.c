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
typedef  int /*<<< orphan*/  ae_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_LOCK_ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AE_PHY_DBG_ADDR ; 
 int /*<<< orphan*/  AE_PHY_DBG_DATA ; 
 int AE_PHY_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_PHY_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ae_powersave_enable(ae_softc_t *sc)
{
	uint32_t val;
	
	AE_LOCK_ASSERT(sc);

	/*
	 * XXX magic numbers.
	 */
	AE_PHY_WRITE(sc, AE_PHY_DBG_ADDR, 0);
	val = AE_PHY_READ(sc, AE_PHY_DBG_DATA);
	AE_PHY_WRITE(sc, AE_PHY_DBG_ADDR, val | 0x1000);
	AE_PHY_WRITE(sc, AE_PHY_DBG_ADDR, 2);
	AE_PHY_WRITE(sc, AE_PHY_DBG_DATA, 0x3000);
	AE_PHY_WRITE(sc, AE_PHY_DBG_ADDR, 3);
	AE_PHY_WRITE(sc, AE_PHY_DBG_DATA, 0);
}