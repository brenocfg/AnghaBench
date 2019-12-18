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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct hrowpic_softc {int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; } ;

/* Variables and functions */
 scalar_t__ HPIC_1ST_OFFSET ; 
 scalar_t__ HPIC_PRIMARY ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint32_t
hrowpic_read_reg(struct hrowpic_softc *sc, u_int reg, u_int bank)
{
	if (bank == HPIC_PRIMARY)
		reg += HPIC_1ST_OFFSET;

	return (bus_space_read_4(sc->sc_bt, sc->sc_bh, reg));
}