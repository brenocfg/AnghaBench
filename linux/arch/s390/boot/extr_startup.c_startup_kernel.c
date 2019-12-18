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
struct TYPE_2__ {unsigned long default_lma; int /*<<< orphan*/  (* entry ) () ;int /*<<< orphan*/  image_size; int /*<<< orphan*/  dynsym_start; int /*<<< orphan*/  rela_dyn_end; int /*<<< orphan*/  rela_dyn_start; int /*<<< orphan*/  bootdata_preserved_off; int /*<<< orphan*/  bootdata_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_KERNEL_UNCOMPRESSED ; 
 int /*<<< orphan*/  CONFIG_RANDOMIZE_BASE ; 
 int /*<<< orphan*/  CONFIG_RELOCATABLE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long __kaslr_offset ; 
 int /*<<< orphan*/  clear_bss_section () ; 
 int /*<<< orphan*/  copy_bootdata () ; 
 void* decompress_kernel () ; 
 int /*<<< orphan*/  detect_memory () ; 
 unsigned long get_random_base (unsigned long) ; 
 int /*<<< orphan*/  handle_relocs (unsigned long) ; 
 scalar_t__ kaslr_enabled ; 
 unsigned long mem_safe_offset () ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_boot_command_line () ; 
 unsigned long read_ipl_report (unsigned long) ; 
 int /*<<< orphan*/  rescue_initrd (unsigned long) ; 
 int /*<<< orphan*/  sclp_early_read_info () ; 
 int /*<<< orphan*/  setup_boot_command_line () ; 
 int /*<<< orphan*/  setup_memory_end () ; 
 int /*<<< orphan*/  store_ipl_parmblock () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  uv_query_info () ; 
 TYPE_1__ vmlinux ; 

void startup_kernel(void)
{
	unsigned long random_lma;
	unsigned long safe_addr;
	void *img;

	store_ipl_parmblock();
	safe_addr = mem_safe_offset();
	safe_addr = read_ipl_report(safe_addr);
	uv_query_info();
	rescue_initrd(safe_addr);
	sclp_early_read_info();
	setup_boot_command_line();
	parse_boot_command_line();
	setup_memory_end();
	detect_memory();

	random_lma = __kaslr_offset = 0;
	if (IS_ENABLED(CONFIG_RANDOMIZE_BASE) && kaslr_enabled) {
		random_lma = get_random_base(safe_addr);
		if (random_lma) {
			__kaslr_offset = random_lma - vmlinux.default_lma;
			img = (void *)vmlinux.default_lma;
			vmlinux.default_lma += __kaslr_offset;
			vmlinux.entry += __kaslr_offset;
			vmlinux.bootdata_off += __kaslr_offset;
			vmlinux.bootdata_preserved_off += __kaslr_offset;
			vmlinux.rela_dyn_start += __kaslr_offset;
			vmlinux.rela_dyn_end += __kaslr_offset;
			vmlinux.dynsym_start += __kaslr_offset;
		}
	}

	if (!IS_ENABLED(CONFIG_KERNEL_UNCOMPRESSED)) {
		img = decompress_kernel();
		memmove((void *)vmlinux.default_lma, img, vmlinux.image_size);
	} else if (__kaslr_offset)
		memcpy((void *)vmlinux.default_lma, img, vmlinux.image_size);

	clear_bss_section();
	copy_bootdata();
	if (IS_ENABLED(CONFIG_RELOCATABLE))
		handle_relocs(__kaslr_offset);

	if (__kaslr_offset) {
		/* Clear non-relocated kernel */
		if (IS_ENABLED(CONFIG_KERNEL_UNCOMPRESSED))
			memset(img, 0, vmlinux.image_size);
	}
	vmlinux.entry();
}