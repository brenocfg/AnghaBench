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
struct mtkswitch_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_UNLOCK (struct mtkswitch_softc*) ; 
 struct mtkswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mtkswitch_unlock(device_t dev)
{
	struct mtkswitch_softc *sc = device_get_softc(dev);

	MTKSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	MTKSWITCH_UNLOCK(sc);
}