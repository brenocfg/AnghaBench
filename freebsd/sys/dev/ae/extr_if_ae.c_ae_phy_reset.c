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
 int /*<<< orphan*/  AE_PHY_ENABLE ; 
 int /*<<< orphan*/  AE_PHY_ENABLE_REG ; 
 int /*<<< orphan*/  AE_WRITE_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static void
ae_phy_reset(ae_softc_t *sc)
{

	AE_WRITE_4(sc, AE_PHY_ENABLE_REG, AE_PHY_ENABLE);
	DELAY(1000);	/* XXX: pause(9) ? */
}