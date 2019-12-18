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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct octeon_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_rw_core_mem (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

uint32_t
lio_read_device_mem32(struct octeon_device *oct, uint64_t coreaddr)
{
	__be32	ret;

	lio_pci_rw_core_mem(oct, coreaddr, (uint8_t *)&ret, 4, 1);

	return (be32toh(ret));
}