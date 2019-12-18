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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fsi_slave {int size; scalar_t__ id; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int fsi_slave_calc_addr(struct fsi_slave *slave, uint32_t *addrp,
		uint8_t *idp)
{
	uint32_t addr = *addrp;
	uint8_t id = *idp;

	if (addr > slave->size)
		return -EINVAL;

	/* For 23 bit addressing, we encode the extra two bits in the slave
	 * id (and the slave's actual ID needs to be 0).
	 */
	if (addr > 0x1fffff) {
		if (slave->id != 0)
			return -EINVAL;
		id = (addr >> 21) & 0x3;
		addr &= 0x1fffff;
	}

	*addrp = addr;
	*idp = id;
	return 0;
}