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
struct TYPE_2__ {size_t size; void const* addr; } ;
struct fiq_req {int flags; int /*<<< orphan*/  reg; TYPE_1__ unmap; } ;

/* Variables and functions */
 int CNS3XXX_UNMAP_AREA ; 
 int /*<<< orphan*/  FIQ_GENERATE ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int /*<<< orphan*/  fiq_data ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  smp_mb () ; 
 struct fiq_req* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v6_dma_unmap_area (void const*,size_t,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fiq_dma_unmap_area(const void *addr, size_t size, int dir)
{
	unsigned long flags;
	struct fiq_req *req;

	raw_local_irq_save(flags);
	/* currently, not possible to take cpu0 down, so only check cpu1 */
	if (!cpu_online(1)) {
		raw_local_irq_restore(flags);
		v6_dma_unmap_area(addr, size, dir);
		return;
	}

	req = this_cpu_ptr(&fiq_data);
	req->unmap.addr = addr;
	req->unmap.size = size;
	req->flags = dir | CNS3XXX_UNMAP_AREA;
	smp_mb();

	writel_relaxed(FIQ_GENERATE, req->reg);

	v6_dma_unmap_area(addr, size, dir);
	while (req->flags)
		barrier();

	raw_local_irq_restore(flags);
}