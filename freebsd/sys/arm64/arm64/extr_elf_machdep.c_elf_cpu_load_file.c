#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_3__ {int id; int /*<<< orphan*/  size; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_icache_sync_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
elf_cpu_load_file(linker_file_t lf)
{

	if (lf->id != 1)
		cpu_icache_sync_range((vm_offset_t)lf->address, lf->size);
	return (0);
}