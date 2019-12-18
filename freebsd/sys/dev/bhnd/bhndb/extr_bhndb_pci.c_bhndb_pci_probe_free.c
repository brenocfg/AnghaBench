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
struct bhndb_pci_probe {int /*<<< orphan*/  hr; int /*<<< orphan*/  erom; int /*<<< orphan*/  cores; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  bhnd_erom_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_erom_free_core_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhndb_release_host_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bhndb_pci_probe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bhndb_pci_probe_free(struct bhndb_pci_probe *probe)
{
	bhnd_erom_free_core_table(probe->erom, probe->cores);
	bhnd_erom_free(probe->erom);
	bhndb_release_host_resources(probe->hr);
	free(probe, M_BHND);
}