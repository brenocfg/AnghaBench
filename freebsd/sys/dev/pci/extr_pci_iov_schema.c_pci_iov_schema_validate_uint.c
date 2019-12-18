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
typedef  scalar_t__ uint64_t ;
struct config_type_validator {scalar_t__ limit; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvlist_exists_number (int /*<<< orphan*/  const*,char const*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static int
pci_iov_schema_validate_uint(const struct config_type_validator * validator,
   const nvlist_t *config, const char *name)
{
	uint64_t value;

	if (!nvlist_exists_number(config, name))
		return (EINVAL);

	value = nvlist_get_number(config, name);

	if (value > validator->limit)
		return (EINVAL);

	return (0);
}