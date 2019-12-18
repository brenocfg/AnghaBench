#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  ddump_saved; } ;
typedef  TYPE_1__ ocs_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_ddump (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 scalar_t__ ocs_textbuf_get_written (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_textbuf_initialized (int /*<<< orphan*/ *) ; 

int32_t
ocs_save_ddump(ocs_t *ocs, uint32_t flags, uint32_t qentries)
{
	if (ocs_textbuf_get_written(&ocs->ddump_saved) > 0) {
		ocs_log_debug(ocs, "Saved ddump already exists\n");
		return 1;
	}

	if (!ocs_textbuf_initialized(&ocs->ddump_saved)) {
		ocs_log_err(ocs, "Saved ddump not allocated\n");
		return -1;
	}

	ocs_log_debug(ocs, "Saving ddump\n");
	ocs_ddump(ocs, &ocs->ddump_saved, flags, qentries);
	ocs_log_debug(ocs, "Saved ddump: %d bytes written\n", ocs_textbuf_get_written(&ocs->ddump_saved));
	return 0;
}