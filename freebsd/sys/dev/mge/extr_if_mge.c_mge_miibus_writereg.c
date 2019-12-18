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
 int /*<<< orphan*/  mv_write_ext_phy (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  switch_attached ; 

__attribute__((used)) static int
mge_miibus_writereg(device_t dev, int phy, int reg, int value)
{
	struct mge_softc *sc;
	sc = device_get_softc(dev);

	KASSERT(!switch_attached, ("miibus used with switch attached"));

	mv_write_ext_phy(dev, phy, reg, value);

	return (0);
}