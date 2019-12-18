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
typedef  int uint16_t ;
struct mv88e61xxphy_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E61XX_GLOBAL ; 
 int /*<<< orphan*/  MV88E61XX_GLOBAL_VTU_OP ; 
 int MV88E61XX_GLOBAL_VTU_OP_BUSY ; 
 int MV88E61XX_READ (struct mv88e61xxphy_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mv88e61xxphy_vtu_wait(struct mv88e61xxphy_softc *sc)
{
	uint16_t val;

	for (;;) {
		val = MV88E61XX_READ(sc, MV88E61XX_GLOBAL, MV88E61XX_GLOBAL_VTU_OP);
		if ((val & MV88E61XX_GLOBAL_VTU_OP_BUSY) == 0)
			return;
	}
}