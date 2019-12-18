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
struct aac_ident {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 struct aac_ident* aac_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int
aac_pci_probe(device_t dev)
{
	const struct aac_ident *id;

	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	if ((id = aac_find_ident(dev)) != NULL) {
		device_set_desc(dev, id->desc);
		return(BUS_PROBE_DEFAULT);
	}
	return(ENXIO);
}