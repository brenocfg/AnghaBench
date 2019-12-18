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
struct mps_softc {int /*<<< orphan*/  dpm_pg0; int /*<<< orphan*/  dpm_flush_entry; int /*<<< orphan*/  dpm_entry_used; int /*<<< orphan*/  enclosure_table; int /*<<< orphan*/  removal_table; int /*<<< orphan*/  mapping_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MPT2 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mps_mapping_free_memory(struct mps_softc *sc)
{
	free(sc->mapping_table, M_MPT2);
	free(sc->removal_table, M_MPT2);
	free(sc->enclosure_table, M_MPT2);
	free(sc->dpm_entry_used, M_MPT2);
	free(sc->dpm_flush_entry, M_MPT2);
	free(sc->dpm_pg0, M_MPT2);
}