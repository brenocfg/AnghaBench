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
struct xl_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  XL_SEL_WIN (int) ; 
 struct xl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mii_bitbang_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  xl_mii_bitbang_ops ; 

__attribute__((used)) static int
xl_miibus_readreg(device_t dev, int phy, int reg)
{
	struct xl_softc		*sc;

	sc = device_get_softc(dev);

	/* Select the window 4. */
	XL_SEL_WIN(4);

	return (mii_bitbang_readreg(dev, &xl_mii_bitbang_ops, phy, reg));
}