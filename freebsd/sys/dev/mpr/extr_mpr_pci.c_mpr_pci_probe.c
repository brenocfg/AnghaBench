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
struct mpr_ident {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mpr_ident* mpr_find_ident (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpr_pci_probe(device_t dev)
{
	struct mpr_ident *id;

	if ((id = mpr_find_ident(dev)) != NULL) {
		device_set_desc(dev, id->desc);
		return (BUS_PROBE_DEFAULT);
	}
	return (ENXIO);
}