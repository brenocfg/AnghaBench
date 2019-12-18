#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  ddump_saved; } ;
typedef  TYPE_1__ ocs_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SAVED_DUMP_SIZE ; 
 TYPE_1__* ocs_get_instance (scalar_t__) ; 
 scalar_t__ ocs_save_ddump (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ ocs_textbuf_alloc (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_textbuf_initialized (int /*<<< orphan*/ *) ; 

int32_t
ocs_save_ddump_all(uint32_t flags, uint32_t qentries, uint32_t alloc_flag)
{
	ocs_t *ocs;
	uint32_t i;
	int32_t rc = 0;

	for (i = 0; (ocs = ocs_get_instance(i)) != NULL; i++) {
		if (alloc_flag && (!ocs_textbuf_initialized(&ocs->ddump_saved))) {
			rc = ocs_textbuf_alloc(ocs, &ocs->ddump_saved, DEFAULT_SAVED_DUMP_SIZE);
			if (rc) {
				break;
			}
		}

		rc = ocs_save_ddump(ocs, flags, qentries);
		if (rc < 0) {
			break;
		}
	}
	return rc;
}