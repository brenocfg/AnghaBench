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
struct mmc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 struct mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_scan (struct mmc_softc*) ; 

__attribute__((used)) static int
mmc_resume(device_t dev)
{
	struct mmc_softc *sc = device_get_softc(dev);

	mmc_scan(sc);
	return (bus_generic_resume(dev));
}