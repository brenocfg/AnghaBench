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
struct octeon_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_rw_core_mem (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

uint64_t
lio_read_device_mem64(struct octeon_device *oct, uint64_t coreaddr)
{
	__be64	ret;

	lio_pci_rw_core_mem(oct, coreaddr, (uint8_t *)&ret, 8, 1);

	return (be64toh(ret));
}