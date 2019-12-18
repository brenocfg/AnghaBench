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
struct bhndb_softc {int /*<<< orphan*/  bridge_core; int /*<<< orphan*/  parent_dev; } ;
struct bhnd_core_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BHNDB_BUS_IS_CORE_DISABLED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhnd_core_info*) ; 
 scalar_t__ BHND_DEVCLASS_SUPPORTS_HOSTB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_core_class (struct bhnd_core_info*) ; 
 int /*<<< orphan*/  bhnd_cores_equal (struct bhnd_core_info*,int /*<<< orphan*/ *) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bhndb_is_core_disabled(device_t dev, device_t child,
    struct bhnd_core_info *core)
{
	struct bhndb_softc	*sc;

	sc = device_get_softc(dev);

	/* Try to defer to the bhndb bus parent */
	if (BHNDB_BUS_IS_CORE_DISABLED(sc->parent_dev, dev, core))
		return (true);

	/* Otherwise, we treat bridge-capable cores as unpopulated if they're
	 * not the configured host bridge */
	if (BHND_DEVCLASS_SUPPORTS_HOSTB(bhnd_core_class(core)))
		return (!bhnd_cores_equal(core, &sc->bridge_core));

	/* Assume the core is populated */
	return (false);
}