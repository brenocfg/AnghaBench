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
struct idad_softc {int /*<<< orphan*/  disk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idad_detach(device_t dev)
{
	struct idad_softc *drv;

	drv = (struct idad_softc *)device_get_softc(dev);
	disk_destroy(drv->disk);
	return (0);
}