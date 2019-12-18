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
struct bfe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_LOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  BFE_UNLOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_stop (struct bfe_softc*) ; 
 struct bfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bfe_suspend(device_t dev)
{
	struct bfe_softc *sc;

	sc = device_get_softc(dev);
	BFE_LOCK(sc);
	bfe_stop(sc);
	BFE_UNLOCK(sc);

	return (0);
}