#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ops; scalar_t__ dump_registered; scalar_t__ dump_active; int /*<<< orphan*/  fadump_supported; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fadump_cleanup ) (TYPE_2__*) ;int /*<<< orphan*/  (* fadump_unregister ) (TYPE_2__*) ;int /*<<< orphan*/  (* fadump_invalidate ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  crash_mrange_info ; 
 int /*<<< orphan*/  fadump_free_mem_ranges (int /*<<< orphan*/ *) ; 
 TYPE_2__ fw_dump ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

void fadump_cleanup(void)
{
	if (!fw_dump.fadump_supported)
		return;

	/* Invalidate the registration only if dump is active. */
	if (fw_dump.dump_active) {
		pr_debug("Invalidating firmware-assisted dump registration\n");
		fw_dump.ops->fadump_invalidate(&fw_dump);
	} else if (fw_dump.dump_registered) {
		/* Un-register Firmware-assisted dump if it was registered. */
		fw_dump.ops->fadump_unregister(&fw_dump);
		fadump_free_mem_ranges(&crash_mrange_info);
	}

	if (fw_dump.ops->fadump_cleanup)
		fw_dump.ops->fadump_cleanup(&fw_dump);
}