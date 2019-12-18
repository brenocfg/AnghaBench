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
struct TYPE_2__ {int /*<<< orphan*/  start_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASAN_SHADOW_START ; 
 size_t KASAN_START_NR ; 
 int /*<<< orphan*/  PAGE_END ; 
 size_t PAGE_END_NR ; 
 TYPE_1__* address_markers ; 
 int /*<<< orphan*/  kernel_ptdump_info ; 
 int /*<<< orphan*/  ptdump_debugfs_register (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ptdump_initialize () ; 

__attribute__((used)) static int ptdump_init(void)
{
	address_markers[PAGE_END_NR].start_address = PAGE_END;
#ifdef CONFIG_KASAN
	address_markers[KASAN_START_NR].start_address = KASAN_SHADOW_START;
#endif
	ptdump_initialize();
	ptdump_debugfs_register(&kernel_ptdump_info, "kernel_page_tables");
	return 0;
}