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
struct sfxge_softc {scalar_t__ family; int /*<<< orphan*/ * enp; } ;
typedef  int /*<<< orphan*/  efx_nvram_type_t ;
typedef  int /*<<< orphan*/  efx_nic_t ;

/* Variables and functions */
 scalar_t__ EFX_FAMILY_SIENA ; 
 int /*<<< orphan*/  EFX_NVRAM_DYNAMIC_CFG ; 
 int efx_nvram_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_nvram_rw_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int efx_nvram_rw_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
sfxge_nvram_erase(struct sfxge_softc *sc, efx_nvram_type_t type)
{
	efx_nic_t *enp = sc->enp;
	size_t chunk_size;
	int rc = 0;

	if (type == EFX_NVRAM_DYNAMIC_CFG && sc->family == EFX_FAMILY_SIENA)
		return (0);

	if ((rc = efx_nvram_rw_start(enp, type, &chunk_size)) != 0)
		return (rc);

	rc = efx_nvram_erase(enp, type);

	efx_nvram_rw_finish(enp, type, NULL);
	return (rc);
}