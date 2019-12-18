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
 int /*<<< orphan*/  ADM6996FC_LOCK_ASSERT (struct adm6996fc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM6996FC_UNLOCK (struct adm6996fc_softc*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct adm6996fc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
adm6996fc_unlock(device_t dev)
{
	struct adm6996fc_softc *sc;

	sc = device_get_softc(dev);

	ADM6996FC_LOCK_ASSERT(sc, MA_OWNED);
	ADM6996FC_UNLOCK(sc);
}