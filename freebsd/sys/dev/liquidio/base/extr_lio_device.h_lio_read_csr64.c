#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct octeon_device {TYPE_1__* mem_bus_space; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int bus_space_read_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int lio_read_csr32 (struct octeon_device*,scalar_t__) ; 

__attribute__((used)) static inline uint64_t
lio_read_csr64(struct octeon_device *oct, uint32_t reg)
{

#ifdef __i386__
	return (lio_read_csr32(oct, reg) |
			((uint64_t)lio_read_csr32(oct, reg + 4) << 32));
#else
	return (bus_space_read_8(oct->mem_bus_space[0].tag,
				 oct->mem_bus_space[0].handle, reg));
#endif
}