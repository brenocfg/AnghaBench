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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 unsigned int INFINIBAND_ALEN ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int ipoib_mcast_addr_is_valid(const u8 *addr, unsigned int addrlen,
				     const u8 *broadcast)
{
	if (addrlen != INFINIBAND_ALEN)
		return 0;
	/* reserved QPN, prefix, scope */
	if (memcmp(addr, broadcast, 6))
		return 0;
	/* signature lower, pkey */
	if (memcmp(addr + 7, broadcast + 7, 3))
		return 0;
	return 1;
}