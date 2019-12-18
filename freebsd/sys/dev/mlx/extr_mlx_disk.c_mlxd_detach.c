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
struct mlxd_softc {int /*<<< orphan*/  mlxd_disk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxd_detach(device_t dev)
{
    struct mlxd_softc *sc = (struct mlxd_softc *)device_get_softc(dev);

    debug_called(1);

    disk_destroy(sc->mlxd_disk);

    return(0);
}