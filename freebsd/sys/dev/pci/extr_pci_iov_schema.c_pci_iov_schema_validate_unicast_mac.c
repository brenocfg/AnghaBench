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
typedef  int /*<<< orphan*/  uint8_t ;
struct config_type_validator {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_IS_MULTICAST (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvlist_exists_binary (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * nvlist_get_binary (int /*<<< orphan*/  const*,char const*,size_t*) ; 

__attribute__((used)) static int
pci_iov_schema_validate_unicast_mac(
   const struct config_type_validator * validator,
   const nvlist_t *config, const char *name)
{
	const uint8_t *mac;
	size_t size;

	if (!nvlist_exists_binary(config, name))
		return (EINVAL);

	mac = nvlist_get_binary(config, name, &size);

	if (size != ETHER_ADDR_LEN)
		return (EINVAL);

	if (ETHER_IS_MULTICAST(mac))
		return (EINVAL);

	return (0);
}