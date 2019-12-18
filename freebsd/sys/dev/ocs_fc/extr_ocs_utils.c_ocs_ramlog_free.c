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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_5__ {size_t textbuf_count; struct TYPE_5__* textbufs; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ ocs_ramlog_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ocs_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_textbuf_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
ocs_ramlog_free(ocs_t *ocs, ocs_ramlog_t *ramlog)
{
	uint32_t i;

	if (ramlog != NULL) {
		ocs_lock_free(&ramlog->lock);
		if (ramlog->textbufs) {
			for (i = 0; i < ramlog->textbuf_count; i ++) {
				ocs_textbuf_free(ocs, &ramlog->textbufs[i]);
			}

			ocs_free(ocs, ramlog->textbufs, ramlog->textbuf_count*sizeof(*ramlog->textbufs));
			ramlog->textbufs = NULL;
		}
		ocs_free(ocs, ramlog, sizeof(*ramlog));
	}
}