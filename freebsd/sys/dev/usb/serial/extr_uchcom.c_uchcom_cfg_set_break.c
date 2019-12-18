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
typedef  scalar_t__ uint8_t ;
struct ucom_softc {struct uchcom_softc* sc_parent; } ;
struct uchcom_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ UCHCOM_BRK_MASK ; 
 scalar_t__ UCHCOM_LCR1_TX ; 
 int /*<<< orphan*/  UCHCOM_REG_BREAK1 ; 
 int /*<<< orphan*/  UCHCOM_REG_LCR1 ; 
 int /*<<< orphan*/  uchcom_read_reg (struct uchcom_softc*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  uchcom_write_reg (struct uchcom_softc*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
uchcom_cfg_set_break(struct ucom_softc *ucom, uint8_t onoff)
{
	struct uchcom_softc *sc = ucom->sc_parent;
	uint8_t brk1;
	uint8_t brk2;

	uchcom_read_reg(sc, UCHCOM_REG_BREAK1, &brk1, UCHCOM_REG_LCR1, &brk2);
	if (onoff) {
		/* on - clear bits */
		brk1 &= ~UCHCOM_BRK_MASK;
		brk2 &= ~UCHCOM_LCR1_TX;
	} else {
		/* off - set bits */
		brk1 |= UCHCOM_BRK_MASK;
		brk2 |= UCHCOM_LCR1_TX;
	}
	uchcom_write_reg(sc, UCHCOM_REG_BREAK1, brk1, UCHCOM_REG_LCR1, brk2);
}