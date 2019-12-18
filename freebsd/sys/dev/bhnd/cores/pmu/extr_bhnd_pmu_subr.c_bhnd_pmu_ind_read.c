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
typedef  int /*<<< orphan*/  uint32_t ;
struct bhnd_pmu_io {int /*<<< orphan*/  (* rd4 ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* wr4 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void*) ; 

uint32_t
bhnd_pmu_ind_read(const struct bhnd_pmu_io *io, void *io_ctx, bus_size_t addr,
    bus_size_t data, uint32_t reg)
{
	io->wr4(addr, reg, io_ctx);
	return (io->rd4(data, io_ctx));
}