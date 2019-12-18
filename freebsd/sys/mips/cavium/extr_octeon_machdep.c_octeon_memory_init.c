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
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int int64_t ;
struct TYPE_2__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int /*<<< orphan*/  MIPS_DIRECT_MAPPABLE (int) ; 
 int /*<<< orphan*/  MIPS_KSEG0_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int PHYS_AVAIL_ENTRIES ; 
 scalar_t__ btoc (int) ; 
 int cvmx_bootmem_available_mem (int) ; 
 int cvmx_bootmem_phy_alloc (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 int* dump_avail ; 
 int /*<<< orphan*/  end ; 
 int* phys_avail ; 
 scalar_t__ physmem ; 
 scalar_t__ realmem ; 
 int round_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
octeon_memory_init(void)
{
	vm_paddr_t phys_end;
	int64_t addr;
	unsigned i, j;

	phys_end = round_page(MIPS_KSEG0_TO_PHYS((vm_offset_t)&end));

	if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM) {
		/* Simulator we limit to 96 meg */
		phys_avail[0] = phys_end;
		phys_avail[1] = 96 << 20;

		dump_avail[0] = phys_avail[0];
		dump_avail[1] = phys_avail[1];

		realmem = physmem = btoc(phys_avail[1] - phys_avail[0]);
		return;
	}

	/*
	 * Allocate memory from bootmem 1MB at a time and merge
	 * adjacent entries.
	 */
	i = 0;
	while (i < PHYS_AVAIL_ENTRIES) {
		/*
		 * If there is less than 2MB of memory available in 128-byte
		 * blocks, do not steal any more memory.  We need to leave some
		 * memory for the command queues to be allocated out of.
		 */
		if (cvmx_bootmem_available_mem(128) < 2 << 20)
			break;

		addr = cvmx_bootmem_phy_alloc(1 << 20, phys_end,
					      ~(vm_paddr_t)0, PAGE_SIZE, 0);
		if (addr == -1)
			break;

		/*
		 * The SDK needs to be able to easily map any memory that might
		 * come to it e.g. in the form of an mbuf.  Because on !n64 we
		 * can't direct-map some addresses and we don't want to manage
		 * temporary mappings within the SDK, don't feed memory that
		 * can't be direct-mapped to the kernel.
		 */
#if !defined(__mips_n64)
		if (!MIPS_DIRECT_MAPPABLE(addr + (1 << 20) - 1))
			continue;
#endif

		physmem += btoc(1 << 20);

		if (i > 0 && phys_avail[i - 1] == addr) {
			phys_avail[i - 1] += 1 << 20;
			continue;
		}

		phys_avail[i + 0] = addr;
		phys_avail[i + 1] = addr + (1 << 20);

		i += 2;
	}

	for (j = 0; j < i; j++)
		dump_avail[j] = phys_avail[j];

	realmem = physmem;
}