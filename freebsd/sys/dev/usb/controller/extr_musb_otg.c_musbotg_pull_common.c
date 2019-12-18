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
struct musbotg_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ MUSB2_MASK_SOFTC ; 
 scalar_t__ MUSB2_READ_1 (struct musbotg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB2_REG_POWER ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
musbotg_pull_common(struct musbotg_softc *sc, uint8_t on)
{
	uint8_t temp;

	temp = MUSB2_READ_1(sc, MUSB2_REG_POWER);
	if (on)
		temp |= MUSB2_MASK_SOFTC;
	else
		temp &= ~MUSB2_MASK_SOFTC;

	MUSB2_WRITE_1(sc, MUSB2_REG_POWER, temp);
}