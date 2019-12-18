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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  void* jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_dcache_wb_range (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_icache_sync_range (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ish ; 
 void* kdb_jmpbuf (void*) ; 
 int setjmp (void*) ; 

int
db_write_bytes(vm_offset_t addr, size_t size, char *data)
{
	jmp_buf jb;
	void *prev_jb;
	char *dst;
	int ret;

	prev_jb = kdb_jmpbuf(jb);
	ret = setjmp(jb);
	if (ret == 0) {
		dst = (char *)addr;
		while (size-- > 0)
			*dst++ = *data++;

		dsb(ish);

		/* Clean D-cache and invalidate I-cache */
		cpu_dcache_wb_range(addr, (vm_size_t)size);
		cpu_icache_sync_range(addr, (vm_size_t)size);
	}
	(void)kdb_jmpbuf(prev_jb);

	return (ret);
}