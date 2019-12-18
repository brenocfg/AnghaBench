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
struct dmar_unit {int dummy; } ;
typedef  int /*<<< orphan*/  ACPI_DMAR_PCI_PATH ;

/* Variables and functions */
 struct dmar_unit* device_get_softc (int /*<<< orphan*/ *) ; 
 int dmar_devcnt ; 
 int /*<<< orphan*/ ** dmar_devs ; 
 scalar_t__ dmar_match_by_path (struct dmar_unit*,int,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dmar_unit *
dmar_find_by_scope(int dev_domain, int dev_busno,
    const ACPI_DMAR_PCI_PATH *dev_path, int dev_path_len)
{
	struct dmar_unit *unit;
	int i;

	for (i = 0; i < dmar_devcnt; i++) {
		if (dmar_devs[i] == NULL)
			continue;
		unit = device_get_softc(dmar_devs[i]);
		if (dmar_match_by_path(unit, dev_domain, dev_busno, dev_path,
		    dev_path_len, NULL))
			return (unit);
	}
	return (NULL);
}