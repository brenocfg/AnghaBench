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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_4__ {size_t cur_textbuf_idx; int /*<<< orphan*/  lock; int /*<<< orphan*/ * cur_textbuf; int /*<<< orphan*/ * textbufs; int /*<<< orphan*/  initialized; } ;
typedef  TYPE_1__ ocs_ramlog_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 size_t ocs_ramlog_next_idx (TYPE_1__*,size_t) ; 
 int ocs_textbuf_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_textbuf_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_textbuf_vprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

int32_t
ocs_ramlog_vprintf(ocs_ramlog_t *ramlog, const char *fmt, va_list ap)
{
	if (ramlog == NULL || !ramlog->initialized) {
		return -1;
	}

	/* check the current text buffer, if it is almost full (less than 120 characaters), then
	 * roll to the next one.
	 */
	ocs_lock(&ramlog->lock);
	if (ocs_textbuf_remaining(ramlog->cur_textbuf) < 120) {
		ramlog->cur_textbuf_idx = ocs_ramlog_next_idx(ramlog, ramlog->cur_textbuf_idx);
		ramlog->cur_textbuf = &ramlog->textbufs[ramlog->cur_textbuf_idx];
		ocs_textbuf_reset(ramlog->cur_textbuf);
	}

	ocs_textbuf_vprintf(ramlog->cur_textbuf, fmt, ap);
	ocs_unlock(&ramlog->lock);

	return 0;
}