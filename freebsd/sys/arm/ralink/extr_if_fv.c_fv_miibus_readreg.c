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
struct fv_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MII_PREAMBLE ; 
 int MII_RDCMD ; 
 struct fv_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int fv_miibus_readbits (struct fv_softc*,int) ; 
 int /*<<< orphan*/  fv_miibus_turnaround (struct fv_softc*,int) ; 
 int /*<<< orphan*/  fv_miibus_writebits (struct fv_softc*,int,int) ; 
 int /*<<< orphan*/  miibus_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fv_miibus_readreg(device_t dev, int phy, int reg)
{
	struct fv_softc * sc = device_get_softc(dev);
	int		result;

	mtx_lock(&miibus_mtx);
	fv_miibus_writebits(sc, MII_PREAMBLE, 32);
	fv_miibus_writebits(sc, MII_RDCMD, 4);
	fv_miibus_writebits(sc, phy, 5);
	fv_miibus_writebits(sc, reg, 5);
	fv_miibus_turnaround(sc, MII_RDCMD);
	result = fv_miibus_readbits(sc, 16);
	fv_miibus_turnaround(sc, MII_RDCMD);
	mtx_unlock(&miibus_mtx);

	return (result);
}