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
struct bhndb_pci_core {int /*<<< orphan*/  match; } ;
struct bhnd_core_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_PCI_IS_CORE_END (struct bhndb_pci_core*) ; 
 scalar_t__ bhnd_core_matches (struct bhnd_core_info*,int /*<<< orphan*/ *) ; 
 struct bhndb_pci_core* bhndb_pci_cores ; 

__attribute__((used)) static struct bhndb_pci_core *
bhndb_pci_find_core(struct bhnd_core_info *ci)
{
	for (size_t i = 0; !BHNDB_PCI_IS_CORE_END(&bhndb_pci_cores[i]); i++) {
		struct bhndb_pci_core *entry = &bhndb_pci_cores[i];

		if (bhnd_core_matches(ci, &entry->match))
			return (entry);
	}

	return (NULL);
}