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
struct mge_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct mge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mv_read_ext_phy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  switch_attached ; 

__attribute__((used)) static int
mge_miibus_readreg(device_t dev, int phy, int reg)
{
	struct mge_softc *sc;
	sc = device_get_softc(dev);

	KASSERT(!switch_attached, ("miibus used with switch attached"));

	return (mv_read_ext_phy(dev, phy, reg));
}