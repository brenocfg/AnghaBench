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
 int AE_PHY_DBG_POWERSAVE ; 
 int AE_PHY_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_PHY_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static void
ae_powersave_disable(ae_softc_t *sc)
{
	uint32_t val;
	
	AE_LOCK_ASSERT(sc);

	AE_PHY_WRITE(sc, AE_PHY_DBG_ADDR, 0);
	val = AE_PHY_READ(sc, AE_PHY_DBG_DATA);
	if (val & AE_PHY_DBG_POWERSAVE) {
		val &= ~AE_PHY_DBG_POWERSAVE;
		AE_PHY_WRITE(sc, AE_PHY_DBG_DATA, val);
		DELAY(1000);
	}
}