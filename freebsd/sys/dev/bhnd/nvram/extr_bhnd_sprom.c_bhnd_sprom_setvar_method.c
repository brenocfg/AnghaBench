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
struct bhnd_sprom_softc {int /*<<< orphan*/  store; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int bhnd_nvram_store_setvar (int /*<<< orphan*/ ,char const*,void const*,size_t,int /*<<< orphan*/ ) ; 
 struct bhnd_sprom_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_sprom_setvar_method(device_t dev, const char *name, const void *buf,
    size_t len, bhnd_nvram_type type)
{
	struct bhnd_sprom_softc	*sc = device_get_softc(dev);

	return (bhnd_nvram_store_setvar(sc->store, name, buf, len, type));
}