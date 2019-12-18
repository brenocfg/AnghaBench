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
 int /*<<< orphan*/  DEFAULT_SCHEMA_NAME ; 
 int EINVAL ; 
 size_t ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_IS_MULTICAST (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvlist_exists_binary (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_get_binary (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
pci_iov_validate_unicast_mac_default(
   const struct config_type_validator * validator, const nvlist_t *param)
{
	const uint8_t *mac;
	size_t size;

	if (!nvlist_exists_binary(param, DEFAULT_SCHEMA_NAME))
		return (EINVAL);

	mac = nvlist_get_binary(param, DEFAULT_SCHEMA_NAME, &size);
	if (size != ETHER_ADDR_LEN)
		return (EINVAL);

	if (ETHER_IS_MULTICAST(mac))
		return (EINVAL);
	return (0);
}