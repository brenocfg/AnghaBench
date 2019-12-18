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
struct TYPE_2__ {int /*<<< orphan*/  info_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_DETECT_BIN_SEARCH ; 
 int /*<<< orphan*/  MEM_DETECT_DIAG260 ; 
 int /*<<< orphan*/  MEM_DETECT_SCLP_READ_INFO ; 
 int /*<<< orphan*/  MEM_DETECT_SCLP_STOR_INFO ; 
 int /*<<< orphan*/  add_mem_detect_block (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  diag260 () ; 
 scalar_t__ get_mem_detect_end () ; 
 scalar_t__ max_physmem_end ; 
 TYPE_1__ mem_detect ; 
 int /*<<< orphan*/  sclp_early_get_memsize (scalar_t__*) ; 
 int /*<<< orphan*/  sclp_early_read_storage_info () ; 
 int /*<<< orphan*/  search_mem_end () ; 

void detect_memory(void)
{
	sclp_early_get_memsize(&max_physmem_end);

	if (!sclp_early_read_storage_info()) {
		mem_detect.info_source = MEM_DETECT_SCLP_STOR_INFO;
		return;
	}

	if (!diag260()) {
		mem_detect.info_source = MEM_DETECT_DIAG260;
		return;
	}

	if (max_physmem_end) {
		add_mem_detect_block(0, max_physmem_end);
		mem_detect.info_source = MEM_DETECT_SCLP_READ_INFO;
		return;
	}

	search_mem_end();
	mem_detect.info_source = MEM_DETECT_BIN_SEARCH;
	max_physmem_end = get_mem_detect_end();
}