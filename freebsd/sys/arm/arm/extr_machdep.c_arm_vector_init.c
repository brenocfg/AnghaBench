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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int ARM_NVEC ; 
 scalar_t__ ARM_VECTORS_HIGH ; 
 int /*<<< orphan*/  CPU_CONTROL_VECRELOC ; 
 int /*<<< orphan*/  cpu_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icache_sync (scalar_t__,int) ; 
 unsigned int* page0 ; 
 unsigned int* page0_data ; 
 scalar_t__ vector_page ; 

void
arm_vector_init(vm_offset_t va, int which)
{
	unsigned int *vectors = (int *) va;
	unsigned int *vectors_data = vectors + (page0_data - page0);
	int vec;

	/*
	 * Loop through the vectors we're taking over, and copy the
	 * vector's insn and data word.
	 */
	for (vec = 0; vec < ARM_NVEC; vec++) {
		if ((which & (1 << vec)) == 0) {
			/* Don't want to take over this vector. */
			continue;
		}
		vectors[vec] = page0[vec];
		vectors_data[vec] = page0_data[vec];
	}

	/* Now sync the vectors. */
	icache_sync(va, (ARM_NVEC * 2) * sizeof(u_int));

	vector_page = va;
#if __ARM_ARCH < 6
	if (va == ARM_VECTORS_HIGH) {
		/*
		 * Enable high vectors in the system control reg (SCTLR).
		 *
		 * Assume the MD caller knows what it's doing here, and really
		 * does want the vector page relocated.
		 *
		 * Note: This has to be done here (and not just in
		 * cpu_setup()) because the vector page needs to be
		 * accessible *before* cpu_startup() is called.
		 * Think ddb(9) ...
		 */
		cpu_control(CPU_CONTROL_VECRELOC, CPU_CONTROL_VECRELOC);
	}
#endif
}