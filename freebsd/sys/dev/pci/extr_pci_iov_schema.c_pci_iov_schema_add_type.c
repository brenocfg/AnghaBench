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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  nvlist_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_iov_schema_find_validator (char const*) ; 

__attribute__((used)) static void
pci_iov_schema_add_type(nvlist_t *entry, const char *type)
{

	if (pci_iov_schema_find_validator(type) == NULL) {
		nvlist_set_error(entry, EINVAL);
		return;
	}
	nvlist_add_string(entry, "type", type);
}