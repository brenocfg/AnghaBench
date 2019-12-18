#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  (* kernel_entry_t ) (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
struct TYPE_6__ {int /*<<< orphan*/  write; } ;
struct TYPE_5__ {unsigned long (* finalize ) () ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* exit ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _dtb_start ; 
 scalar_t__ _end ; 
 scalar_t__ _initrd_end ; 
 scalar_t__ _initrd_start ; 
 TYPE_3__ console_ops ; 
 int /*<<< orphan*/  dt_fixup_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ dt_ops ; 
 int /*<<< orphan*/  fdt_init (int /*<<< orphan*/ ) ; 
 void* finddevice (char*) ; 
 TYPE_1__ platform_ops ; 
 int /*<<< orphan*/  prep_cmdline (void*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ps3_console_write ; 
 int /*<<< orphan*/  ps3_copy_vectors () ; 
 int /*<<< orphan*/  ps3_exit () ; 
 int /*<<< orphan*/  ps3_repository_read_rm_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprop_val (void*,char*,scalar_t__) ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,scalar_t__ const,int,int) ; 
 unsigned long stub1 () ; 
 int /*<<< orphan*/  stub2 (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void platform_init(void)
{
	const u32 heapsize = 0x1000000 - (u32)_end; /* 16MiB */
	void *chosen;
	unsigned long ft_addr;
	u64 rm_size;

	console_ops.write = ps3_console_write;
	platform_ops.exit = ps3_exit;

	printf("\n-- PS3 bootwrapper --\n");

	simple_alloc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_start);

	chosen = finddevice("/chosen");

	ps3_repository_read_rm_size(&rm_size);
	dt_fixup_memory(0, rm_size);

	if (_initrd_end > _initrd_start) {
		setprop_val(chosen, "linux,initrd-start", (u32)(_initrd_start));
		setprop_val(chosen, "linux,initrd-end", (u32)(_initrd_end));
	}

	prep_cmdline(chosen);

	ft_addr = dt_ops.finalize();

	ps3_copy_vectors();

	printf(" flat tree at 0x%lx\n\r", ft_addr);

	((kernel_entry_t)0)(ft_addr, 0, NULL);

	ps3_exit();
}