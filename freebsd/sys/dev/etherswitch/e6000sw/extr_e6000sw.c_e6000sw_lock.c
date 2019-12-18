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
struct e6000sw_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK (struct e6000sw_softc*) ; 
 int /*<<< orphan*/  E6000SW_LOCK_ASSERT (struct e6000sw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_UNLOCKED ; 
 struct e6000sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
e6000sw_lock(device_t dev)
{
	struct e6000sw_softc *sc;

	sc = device_get_softc(dev);

	E6000SW_LOCK_ASSERT(sc, SA_UNLOCKED);
	E6000SW_LOCK(sc);
}