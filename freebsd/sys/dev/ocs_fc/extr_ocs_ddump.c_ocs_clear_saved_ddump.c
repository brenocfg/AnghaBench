#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ddump_saved; } ;
typedef  TYPE_1__ ocs_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_log_debug (TYPE_1__*,char*) ; 
 scalar_t__ ocs_textbuf_get_written (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_textbuf_reset (int /*<<< orphan*/ *) ; 

int32_t
ocs_clear_saved_ddump(ocs_t *ocs)
{
	/* if there's a saved ddump, copy to newly allocated textbuf */
	if (ocs_textbuf_get_written(&ocs->ddump_saved)) {
		ocs_log_debug(ocs, "saved ddump cleared\n");
		ocs_textbuf_reset(&ocs->ddump_saved);
		return 0;
	} else {
		ocs_log_debug(ocs, "no saved ddump found\n");
		return 1;
	}
}