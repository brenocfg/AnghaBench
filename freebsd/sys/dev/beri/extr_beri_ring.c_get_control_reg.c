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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct beri_softc {scalar_t__ control_read; scalar_t__ control_write; } ;
typedef  int /*<<< orphan*/  control_reg_t ;

/* Variables and functions */
 scalar_t__ READ4 (struct beri_softc*,scalar_t__) ; 

__attribute__((used)) static control_reg_t
get_control_reg(struct beri_softc *sc, int dir)
{
	uint32_t offset;
	uint16_t dst[4];
	control_reg_t c;
	uint16_t *cp;
	int i;

	cp = (uint16_t *)&c;

	offset = dir ? sc->control_write : sc->control_read;
	((uint32_t *)dst)[0] = READ4(sc, offset);
	((uint32_t *)dst)[1] = READ4(sc, offset + 4);

	for (i = 0; i < 4; i++)
		cp[i] = dst[3 - i];

	return (c);
}