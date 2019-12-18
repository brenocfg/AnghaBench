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
 int MII_WRCMD ; 
 struct fv_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fv_miibus_turnaround (struct fv_softc*,int) ; 
 int /*<<< orphan*/  fv_miibus_writebits (struct fv_softc*,int,int) ; 
 int /*<<< orphan*/  miibus_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fv_miibus_writereg(device_t dev, int phy, int reg, int data)
{
	struct fv_softc * sc = device_get_softc(dev);

	mtx_lock(&miibus_mtx);
	fv_miibus_writebits(sc, MII_PREAMBLE, 32);
	fv_miibus_writebits(sc, MII_WRCMD, 4);
	fv_miibus_writebits(sc, phy, 5);
	fv_miibus_writebits(sc, reg, 5);
	fv_miibus_turnaround(sc, MII_WRCMD);
	fv_miibus_writebits(sc, data, 16);
	mtx_unlock(&miibus_mtx);

	return (0);
}