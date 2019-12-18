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
struct bhnd_core_info {int dummy; } ;
struct bhndb_softc {struct bhnd_core_info bridge_core; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_get_hostb_core(device_t dev, device_t child, struct bhnd_core_info *core)
{
	struct bhndb_softc *sc = device_get_softc(dev);

	*core = sc->bridge_core;
	return (0);
}