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
struct sc_info {int /*<<< orphan*/  mpu_intr; int /*<<< orphan*/  mpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_INTE ; 
 int EMU_INTE_MIDIRXENABLE ; 
 int /*<<< orphan*/  emu_intr2 ; 
 int /*<<< orphan*/  emu_mpu_class ; 
 int emu_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mpu401_init (int /*<<< orphan*/ *,struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
emu_midiattach(struct sc_info *sc)
{
	int i;

	i = emu_rd(sc, EMU_INTE, 4);
	i |= EMU_INTE_MIDIRXENABLE;
	emu_wr(sc, EMU_INTE, i, 4);

	sc->mpu = mpu401_init(&emu_mpu_class, sc, emu_intr2, &sc->mpu_intr);
}