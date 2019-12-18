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
struct alc_softc {int alc_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ALC_FLAG_AR816X_FAMILY ; 
 int alc_mii_writereg_813x (struct alc_softc*,int,int,int) ; 
 int alc_mii_writereg_816x (struct alc_softc*,int,int,int) ; 
 struct alc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alc_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct alc_softc *sc;
	int v;

	sc = device_get_softc(dev);
	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) != 0)
		v = alc_mii_writereg_816x(sc, phy, reg, val);
	else
		v = alc_mii_writereg_813x(sc, phy, reg, val);
	return (v);
}