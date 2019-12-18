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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_4__ {scalar_t__ textbuf_base; int textbuf_count; int /*<<< orphan*/ * textbufs; } ;
typedef  TYPE_1__ ocs_ramlog_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_ddump_endsection (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_ddump_section (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ocs_ramlog_next_idx (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ocs_textbuf_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_textbuf_get_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_textbuf_get_written (int /*<<< orphan*/ *) ; 

int32_t
ocs_ddump_ramlog(ocs_textbuf_t *textbuf, ocs_ramlog_t *ramlog)
{
	uint32_t i;
	ocs_textbuf_t *rltextbuf;
	int idx;

	if ((ramlog == NULL) || (ramlog->textbufs == NULL)) {
		return -1;
	}

	ocs_ddump_section(textbuf, "driver-log", 0);

	/* Dump the start of day buffer */
	ocs_ddump_section(textbuf, "startofday", 0);
	/* If textbuf_base is 0, then all buffers are used for recent */
	if (ramlog->textbuf_base) {
		rltextbuf = &ramlog->textbufs[0];
		ocs_textbuf_buffer(textbuf, ocs_textbuf_get_buffer(rltextbuf), ocs_textbuf_get_written(rltextbuf));
	}
	ocs_ddump_endsection(textbuf, "startofday", 0);

	/* Dump the most recent buffers */
	ocs_ddump_section(textbuf, "recent", 0);

	/* start with the next textbuf */
	idx = ocs_ramlog_next_idx(ramlog, ramlog->textbuf_count);

	for (i = ramlog->textbuf_base; i < ramlog->textbuf_count; i ++) {
		rltextbuf = &ramlog->textbufs[idx];
		ocs_textbuf_buffer(textbuf, ocs_textbuf_get_buffer(rltextbuf), ocs_textbuf_get_written(rltextbuf));
		idx = ocs_ramlog_next_idx(ramlog, idx);
	}
	ocs_ddump_endsection(textbuf, "recent", 0);
	ocs_ddump_endsection(textbuf, "driver-log", 0);

	return 0;
}