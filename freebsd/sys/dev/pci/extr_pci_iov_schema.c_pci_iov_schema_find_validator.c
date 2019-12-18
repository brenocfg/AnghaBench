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
typedef  struct config_type_validator {int /*<<< orphan*/  type_name; } const config_type_validator ;

/* Variables and functions */
 int nitems (struct config_type_validator const*) ; 
 struct config_type_validator const* pci_iov_schema_validators ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct config_type_validator *
pci_iov_schema_find_validator(const char *type)
{
	struct config_type_validator *validator;
	int i;

	for (i = 0; i < nitems(pci_iov_schema_validators); i++) {
		validator = &pci_iov_schema_validators[i];
		if (strcmp(type, validator->type_name) == 0)
			return (validator);
	}

	return (NULL);
}