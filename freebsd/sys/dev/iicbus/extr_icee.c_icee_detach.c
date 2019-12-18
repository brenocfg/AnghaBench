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
struct icee_softc {int /*<<< orphan*/  cdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct icee_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
icee_detach(device_t dev)
{
	struct icee_softc *sc = device_get_softc(dev);

	destroy_dev(sc->cdev);
	return (0);
}