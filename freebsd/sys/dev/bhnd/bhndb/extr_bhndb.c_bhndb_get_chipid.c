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
struct bhnd_chipid {int dummy; } ;
struct bhndb_softc {struct bhnd_chipid const chipid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct bhnd_chipid *
bhndb_get_chipid(device_t dev, device_t child)
{
	struct bhndb_softc *sc = device_get_softc(dev);
	return (&sc->chipid);
}