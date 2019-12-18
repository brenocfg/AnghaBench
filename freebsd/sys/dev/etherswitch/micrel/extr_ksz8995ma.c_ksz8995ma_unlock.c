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
struct ksz8995ma_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KSZ8995MA_LOCK_ASSERT (struct ksz8995ma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KSZ8995MA_UNLOCK (struct ksz8995ma_softc*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct ksz8995ma_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ksz8995ma_unlock(device_t dev)
{
	struct ksz8995ma_softc *sc;

	sc = device_get_softc(dev);

	KSZ8995MA_LOCK_ASSERT(sc, MA_OWNED);
	KSZ8995MA_UNLOCK(sc);
}