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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_3__ {size_t textbuf_base; size_t textbuf_count; int cur_textbuf_idx; int /*<<< orphan*/ * textbufs; } ;
typedef  TYPE_1__ ocs_ramlog_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_textbuf_reset (int /*<<< orphan*/ *) ; 

void
ocs_ramlog_clear(ocs_t *ocs, ocs_ramlog_t *ramlog, int clear_start_of_day, int clear_recent)
{
	uint32_t i;

	if (clear_recent) {
		for (i = ramlog->textbuf_base; i < ramlog->textbuf_count; i ++) {
			ocs_textbuf_reset(&ramlog->textbufs[i]);
		}
		ramlog->cur_textbuf_idx = 1;
	}
	if (clear_start_of_day && ramlog->textbuf_base) {
		ocs_textbuf_reset(&ramlog->textbufs[0]);
		/* Set textbuf_base to 0, so that all buffers are available for
		 * recent logs
		 */
		ramlog->textbuf_base = 0;
	}
}