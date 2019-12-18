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
typedef  int /*<<< orphan*/  uint16_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R12A_TXAGC_TABLE_SELECT ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_bb_write (struct rtwn_softc*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

void
r12a_restore_bb_afe_vals(struct rtwn_softc *sc, uint32_t vals[],
    const uint16_t regs[], int size)
{
	int i;

	/* Select page C. */
	rtwn_bb_setbits(sc, R12A_TXAGC_TABLE_SELECT, 0x80000000, 0);

	for (i = 0; i < size; i++)
		rtwn_bb_write(sc, regs[i], vals[i]);
}