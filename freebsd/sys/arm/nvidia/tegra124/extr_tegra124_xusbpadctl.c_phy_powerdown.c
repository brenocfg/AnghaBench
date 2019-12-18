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
struct padctl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN ; 
 int /*<<< orphan*/  ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY ; 
 int /*<<< orphan*/  ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN ; 
 int /*<<< orphan*/  RD4 (struct padctl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct padctl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUSB_PADCTL_ELPG_PROGRAM ; 

__attribute__((used)) static int
phy_powerdown(struct padctl_softc *sc)
{
	uint32_t reg;

	reg = RD4(sc, XUSB_PADCTL_ELPG_PROGRAM);
	reg |= ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY;
	WR4(sc, XUSB_PADCTL_ELPG_PROGRAM, reg);
	DELAY(100);

	reg = RD4(sc, XUSB_PADCTL_ELPG_PROGRAM);
	reg |= ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN;
	WR4(sc, XUSB_PADCTL_ELPG_PROGRAM, reg);
	DELAY(100);

	reg = RD4(sc, XUSB_PADCTL_ELPG_PROGRAM);
	reg |= ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN;
	WR4(sc, XUSB_PADCTL_ELPG_PROGRAM, reg);
	DELAY(100);

	return (0);
}