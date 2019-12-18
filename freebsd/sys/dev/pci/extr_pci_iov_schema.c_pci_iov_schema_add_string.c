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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int IOV_SCHEMA_HASDEFAULT ; 
 int /*<<< orphan*/  NV_FLAG_IGNORE_CASE ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_move_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iov_schema_add_required (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_iov_schema_add_type (int /*<<< orphan*/ *,char*) ; 

void
pci_iov_schema_add_string(nvlist_t *schema, const char *name, uint32_t flags,
    const char *defaultVal)
{
	nvlist_t *entry;

	entry = nvlist_create(NV_FLAG_IGNORE_CASE);
	if (entry == NULL) {
		nvlist_set_error(schema, ENOMEM);
		return;
	}

	pci_iov_schema_add_type(entry, "string");
	if (flags & IOV_SCHEMA_HASDEFAULT)
		nvlist_add_string(entry, "default", defaultVal);
	pci_iov_schema_add_required(entry, flags);

	nvlist_move_nvlist(schema, name, entry);
}