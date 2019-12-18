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
 int /*<<< orphan*/  DEFAULT_SCHEMA_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  nvlist_exists_bool (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_iov_validate_bool_default(const struct config_type_validator * validator,
   const nvlist_t *param)
{

	if (!nvlist_exists_bool(param, DEFAULT_SCHEMA_NAME))
		return (EINVAL);
	return (0);
}