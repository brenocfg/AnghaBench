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
typedef  int uint32_t ;
struct bhnd_pmu_io {int (* rd4 ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* wr4 ) (int /*<<< orphan*/ ,int,void*) ;} ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int UINT32_MAX ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,void*) ; 
 int stub2 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,void*) ; 

void
bhnd_pmu_ind_write(const struct bhnd_pmu_io *io, void *io_ctx, bus_size_t addr,
    bus_size_t data, uint32_t reg, uint32_t val, uint32_t mask)
{
	uint32_t rval;

	io->wr4(addr, reg, io_ctx);

	if (mask != UINT32_MAX) {
		rval = io->rd4(data, io_ctx);
		rval &= ~mask | (val & mask);
	} else {
		rval = val;
	}

	io->wr4(data, rval, io_ctx);
}