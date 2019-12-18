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
typedef  scalar_t__ uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
struct sys_info {int mr_no; TYPE_1__* mr; } ;
struct TYPE_2__ {scalar_t__ flags; int /*<<< orphan*/  size; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ALIGN ; 
 scalar_t__ KERN_MINADDR ; 
 scalar_t__ MR_ATTR_DRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ _start ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ rounddown2 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup2 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 
 char* ub_env_get (char*) ; 
 struct sys_info* ub_get_sys_info () ; 
 scalar_t__ uboot_heap_end ; 

uint64_t
uboot_loadaddr(u_int type, void *data, uint64_t addr)
{
	struct sys_info *si;
	uint64_t sblock, eblock, subldr, eubldr;
	uint64_t biggest_block, this_block;
	uint64_t biggest_size, this_size;
	int i;
	char *envstr;

	if (addr == 0) {
		/*
		 * If the loader_kernaddr environment variable is set, blindly
		 * honor it.  It had better be right.  We force interpretation
		 * of the value in base-16 regardless of any leading 0x prefix,
		 * because that's the U-Boot convention.
		 */
		envstr = ub_env_get("loader_kernaddr");
		if (envstr != NULL)
			return (strtoul(envstr, NULL, 16));

		/*
		 *  Find addr/size of largest DRAM block.  Carve our own address
		 *  range out of the block, because loading the kernel over the
		 *  top ourself is a poor memory-conservation strategy. Avoid
		 *  memory at beginning of the first block of physical ram,
		 *  since u-boot likes to pass args and data there.  Assume that
		 *  u-boot has moved itself to the very top of ram and
		 *  optimistically assume that we won't run into it up there.
		 */
		if ((si = ub_get_sys_info()) == NULL)
			panic("could not retrieve system info");

		biggest_block = 0;
		biggest_size = 0;
		subldr = rounddown2((uintptr_t)_start, KERN_ALIGN);
		eubldr = roundup2((uint64_t)uboot_heap_end, KERN_ALIGN);
		for (i = 0; i < si->mr_no; i++) {
			if (si->mr[i].flags != MR_ATTR_DRAM)
				continue;
			sblock = roundup2((uint64_t)si->mr[i].start,
			    KERN_ALIGN);
			eblock = rounddown2((uint64_t)si->mr[i].start +
			    si->mr[i].size, KERN_ALIGN);
			if (biggest_size == 0)
				sblock += KERN_MINADDR;
			if (subldr >= sblock && subldr < eblock) {
				if (subldr - sblock > eblock - eubldr) {
					this_block = sblock;
					this_size  = subldr - sblock;
				} else {
					this_block = eubldr;
					this_size = eblock - eubldr;
				}
			} else if (subldr < sblock && eubldr < eblock) {
				/* Loader is below or engulfs the sblock */
				this_block = (eubldr < sblock) ? sblock : eubldr;
				this_size = eblock - this_block;
			} else {
				this_block = 0;
				this_size = 0;
			}
			if (biggest_size < this_size) {
				biggest_block = this_block;
				biggest_size  = this_size;
			}
		}
		if (biggest_size == 0)
			panic("Not enough DRAM to load kernel");
#if 0
		printf("Loading kernel into region 0x%08jx-0x%08jx (%ju MiB)\n",
		    (uintmax_t)biggest_block, 
		    (uintmax_t)biggest_block + biggest_size - 1,
		    (uintmax_t)biggest_size / 1024 / 1024);
#endif
		return (biggest_block);
	}
	return roundup2(addr, PAGE_SIZE);
}