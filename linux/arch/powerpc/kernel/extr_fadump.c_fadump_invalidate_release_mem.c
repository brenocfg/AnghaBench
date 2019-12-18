#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ops; int /*<<< orphan*/  boot_mem_top; int /*<<< orphan*/  dump_active; } ;
struct TYPE_5__ {scalar_t__ (* fadump_setup_metadata ) (TYPE_2__*) ;int /*<<< orphan*/  (* fadump_init_mem_struct ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fadump_cleanup () ; 
 int /*<<< orphan*/  fadump_free_cpu_notes_buf () ; 
 int /*<<< orphan*/  fadump_mutex ; 
 int /*<<< orphan*/  fadump_release_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ fw_dump ; 
 int /*<<< orphan*/  memblock_end_of_DRAM () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static void fadump_invalidate_release_mem(void)
{
	mutex_lock(&fadump_mutex);
	if (!fw_dump.dump_active) {
		mutex_unlock(&fadump_mutex);
		return;
	}

	fadump_cleanup();
	mutex_unlock(&fadump_mutex);

	fadump_release_memory(fw_dump.boot_mem_top, memblock_end_of_DRAM());
	fadump_free_cpu_notes_buf();

	/*
	 * Setup kernel metadata and initialize the kernel dump
	 * memory structure for FADump re-registration.
	 */
	if (fw_dump.ops->fadump_setup_metadata &&
	    (fw_dump.ops->fadump_setup_metadata(&fw_dump) < 0))
		pr_warn("Failed to setup kernel metadata!\n");
	fw_dump.ops->fadump_init_mem_struct(&fw_dump);
}