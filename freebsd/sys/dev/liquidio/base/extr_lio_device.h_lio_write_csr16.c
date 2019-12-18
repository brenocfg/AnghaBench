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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct octeon_device {TYPE_1__* mem_bus_space; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lio_write_csr16(struct octeon_device *oct, uint32_t reg, uint16_t val)
{

	bus_space_write_2(oct->mem_bus_space[0].tag,
			  oct->mem_bus_space[0].handle, reg, val);
}