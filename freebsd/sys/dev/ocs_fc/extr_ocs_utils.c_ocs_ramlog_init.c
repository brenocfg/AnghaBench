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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_4__ {int textbuf_count; int textbuf_base; int /*<<< orphan*/  lock; int /*<<< orphan*/  initialized; int /*<<< orphan*/ * textbufs; int /*<<< orphan*/ * cur_textbuf; scalar_t__ cur_textbuf_idx; } ;
typedef  TYPE_1__ ocs_ramlog_t ;

/* Variables and functions */
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_instance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*) ; 
 void* ocs_malloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ocs_ramlog_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int ocs_textbuf_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

ocs_ramlog_t *
ocs_ramlog_init(ocs_t *ocs, uint32_t buffer_len, uint32_t buffer_count)
{
	uint32_t i;
	uint32_t rc;
	ocs_ramlog_t *ramlog;

	ramlog = ocs_malloc(ocs, sizeof(*ramlog), OCS_M_ZERO | OCS_M_NOWAIT);
	if (ramlog == NULL) {
		ocs_log_err(ocs, "ocs_malloc ramlog failed\n");
		return NULL;
	}

	ramlog->textbuf_count = buffer_count;

	ramlog->textbufs = ocs_malloc(ocs, sizeof(*ramlog->textbufs)*buffer_count, OCS_M_ZERO | OCS_M_NOWAIT);
	if (ramlog->textbufs == NULL) {
		ocs_log_err(ocs, "ocs_malloc textbufs failed\n");
		ocs_ramlog_free(ocs, ramlog);
		return NULL;
	}

	for (i = 0; i < buffer_count; i ++) {
		rc = ocs_textbuf_alloc(ocs, &ramlog->textbufs[i], buffer_len);
		if (rc) {
			ocs_log_err(ocs, "ocs_textbuf_alloc failed\n");
			ocs_ramlog_free(ocs, ramlog);
			return NULL;
		}
	}

	ramlog->cur_textbuf_idx = 0;
	ramlog->textbuf_base = 1;
	ramlog->cur_textbuf = &ramlog->textbufs[0];
	ramlog->initialized = TRUE;
	ocs_lock_init(ocs, &ramlog->lock, "ramlog_lock[%d]", ocs_instance(ocs));
	return ramlog;
}