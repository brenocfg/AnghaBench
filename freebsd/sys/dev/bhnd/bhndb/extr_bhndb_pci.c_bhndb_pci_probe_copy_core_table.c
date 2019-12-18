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
typedef  int u_int ;
struct bhndb_pci_probe {int ncores; int /*<<< orphan*/  cores; } ;
struct bhnd_core_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct bhnd_core_info* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct bhnd_core_info*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
bhndb_pci_probe_copy_core_table(struct bhndb_pci_probe *probe,
    struct bhnd_core_info **cores, u_int *ncores)
{
	size_t len = sizeof(**cores) * probe->ncores;

	*cores = malloc(len, M_BHND, M_WAITOK);
	memcpy(*cores, probe->cores, len);

	*ncores = probe->ncores;

	return (0);
}