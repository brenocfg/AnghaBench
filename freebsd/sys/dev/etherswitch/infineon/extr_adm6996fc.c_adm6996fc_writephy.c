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
struct adm6996fc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM6996FC_LOCK (struct adm6996fc_softc*) ; 
 int /*<<< orphan*/  ADM6996FC_LOCK_ASSERT (struct adm6996fc_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ADM6996FC_PHY_C0 ; 
 int ADM6996FC_PHY_SIZE ; 
 int /*<<< orphan*/  ADM6996FC_UNLOCK (struct adm6996fc_softc*) ; 
 int ADM6996FC_WRITEREG (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adm6996fc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adm6996fc_writephy(device_t dev, int phy, int reg, int data)
{
	struct adm6996fc_softc *sc;
	int err;

	sc = device_get_softc(dev);
	ADM6996FC_LOCK_ASSERT(sc, MA_NOTOWNED);

	if (phy < 0 || phy >= 32)
		return (ENXIO);
	if (reg < 0 || reg >= 32)
		return (ENXIO);

	ADM6996FC_LOCK(sc);
	err = ADM6996FC_WRITEREG(device_get_parent(dev),
	    (ADM6996FC_PHY_C0 + ADM6996FC_PHY_SIZE * phy) + reg, data);
	ADM6996FC_UNLOCK(sc);

	return (err);
}