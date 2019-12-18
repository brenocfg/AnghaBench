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
struct config_type_validator {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static int
pci_iov_schema_validate_string(const struct config_type_validator * validator,
   const nvlist_t *config, const char *name)
{

	if (!nvlist_exists_string(config, name))
		return (EINVAL);
	return (0);
}