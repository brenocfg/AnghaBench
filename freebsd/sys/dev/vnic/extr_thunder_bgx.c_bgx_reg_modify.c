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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct bgx {int /*<<< orphan*/  reg_base; } ;
typedef  int bus_space_handle_t ;

/* Variables and functions */
 int bus_read_8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_write_8 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bgx_reg_modify(struct bgx *bgx, uint8_t lmac, uint64_t offset, uint64_t val)
{
	bus_space_handle_t addr;

	addr = ((uint32_t)lmac << 20) + offset;

	bus_write_8(bgx->reg_base, addr, val | bus_read_8(bgx->reg_base, addr));
}