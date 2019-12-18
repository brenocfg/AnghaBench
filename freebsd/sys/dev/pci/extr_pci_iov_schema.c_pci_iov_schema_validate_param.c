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
struct config_type_validator {int (* validate ) (struct config_type_validator const*,int /*<<< orphan*/  const*,char const*) ;} ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char*) ; 
 struct config_type_validator* pci_iov_schema_find_validator (char const*) ; 
 int stub1 (struct config_type_validator const*,int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static int
pci_iov_schema_validate_param(const nvlist_t *schema_param, const char *name,
    const nvlist_t *config)
{
	const struct config_type_validator *validator;
	const char *type;

	type = nvlist_get_string(schema_param, "type");
	validator = pci_iov_schema_find_validator(type);

	KASSERT(validator != NULL,
	    ("Schema was not validated: Unknown type %s", type));

	return (validator->validate(validator, config, name));
}