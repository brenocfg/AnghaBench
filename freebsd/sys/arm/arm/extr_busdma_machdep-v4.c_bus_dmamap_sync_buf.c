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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int bus_dmasync_op_t ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int arm_dcache_align ; 
 int arm_dcache_align_mask ; 
 int /*<<< orphan*/  cpu_dcache_inv_range (int,int) ; 
 int /*<<< orphan*/  cpu_dcache_wb_range (int,int) ; 
 int /*<<< orphan*/  cpu_dcache_wbinv_range (int,int) ; 
 int /*<<< orphan*/  cpu_l2cache_inv_range (int,int) ; 
 int /*<<< orphan*/  cpu_l2cache_wb_range (int,int) ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_range (int,int) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 

__attribute__((used)) static void
bus_dmamap_sync_buf(vm_offset_t buf, int len, bus_dmasync_op_t op,
    int bufaligned)
{
	char _tmp_cl[arm_dcache_align], _tmp_clend[arm_dcache_align];
	register_t s;
	int partial;

	if ((op & BUS_DMASYNC_PREWRITE) && !(op & BUS_DMASYNC_PREREAD)) {
		cpu_dcache_wb_range(buf, len);
		cpu_l2cache_wb_range(buf, len);
	}

	/*
	 * If the caller promises the buffer is properly aligned to a cache line
	 * (even if the call parms make it look like it isn't) we can avoid
	 * attempting to preserve the non-DMA part of the cache line in the
	 * POSTREAD case, but we MUST still do a writeback in the PREREAD case.
	 *
	 * This covers the case of mbufs, where we know how they're aligned and
	 * know the CPU doesn't touch the header in front of the DMA data area
	 * during the IO, but it may have touched it right before invoking the
	 * sync, so a PREREAD writeback is required.
	 *
	 * It also handles buffers we created in bus_dmamem_alloc(), which are
	 * always aligned and padded to cache line size even if the IO length
	 * isn't a multiple of cache line size.  In this case the PREREAD
	 * writeback probably isn't required, but it's harmless.
	 */
	partial = (((vm_offset_t)buf) | len) & arm_dcache_align_mask;

	if (op & BUS_DMASYNC_PREREAD) {
		if (!(op & BUS_DMASYNC_PREWRITE) && !partial) {
			cpu_dcache_inv_range(buf, len);
			cpu_l2cache_inv_range(buf, len);
		} else {
		    	cpu_dcache_wbinv_range(buf, len);
	    		cpu_l2cache_wbinv_range(buf, len);
		}
	}
	if (op & BUS_DMASYNC_POSTREAD) {
		if (partial && !bufaligned) {
			s = intr_disable();
			if (buf & arm_dcache_align_mask)
				memcpy(_tmp_cl, (void *)(buf &
				    ~arm_dcache_align_mask),
				    buf & arm_dcache_align_mask);
			if ((buf + len) & arm_dcache_align_mask)
				memcpy(_tmp_clend,
				    (void *)(buf + len),
				    arm_dcache_align -
				    ((buf + len) & arm_dcache_align_mask));
		}
		cpu_dcache_inv_range(buf, len);
		cpu_l2cache_inv_range(buf, len);
		if (partial && !bufaligned) {
			if (buf & arm_dcache_align_mask)
				memcpy((void *)(buf &
				    ~arm_dcache_align_mask), _tmp_cl,
				    buf & arm_dcache_align_mask);
			if ((buf + len) & arm_dcache_align_mask)
				memcpy((void *)(buf + len),
				    _tmp_clend, arm_dcache_align -
				    ((buf + len) & arm_dcache_align_mask));
			intr_restore(s);
		}
	}
}