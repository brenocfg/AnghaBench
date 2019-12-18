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
struct mtkswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTKSWITCH_READ (struct mtkswitch_softc*,int) ; 

__attribute__((used)) static uint32_t
mtkswitch_reg_read32(struct mtkswitch_softc *sc, int reg)
{

	return (MTKSWITCH_READ(sc, reg));
}