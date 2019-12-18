#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;
typedef  int /*<<< orphan*/  linebuf ;

/* Variables and functions */
 scalar_t__ _isprint (char) ; 
 int /*<<< orphan*/  ocs_debug_is_enabled (int) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ocs_snprintf (char*,int,char*,...) ; 

void
ocs_dump32(uint32_t mask, ocs_os_handle_t os, const char *label, void *buf, uint32_t buf_length)
{
	uint32_t word_count = buf_length / sizeof(uint32_t);
	uint32_t i;
	uint32_t columns = 8;
	uint32_t n;
	uint32_t *wbuf;
	char *cbuf;
	uint32_t addr = 0;
	char linebuf[200];
	char *pbuf = linebuf;

	if (!ocs_debug_is_enabled(mask))
		return;

	if (label)
		ocs_log_debug(os, "%s\n", label);

	wbuf = buf;
	while (word_count > 0) {
		pbuf = linebuf;
		pbuf += ocs_snprintf(pbuf, sizeof(linebuf) - (pbuf-linebuf), "%08X:  ", addr);

		n = word_count;
		if (n > columns)
			n = columns;

		for (i = 0; i < n; i ++)
			pbuf += ocs_snprintf(pbuf, sizeof(linebuf) - (pbuf-linebuf), "%08X ", wbuf[i]);

		for (; i < columns; i ++)
			pbuf += ocs_snprintf(pbuf, sizeof(linebuf) - (pbuf-linebuf), "%8s ", "");

		pbuf += ocs_snprintf(pbuf, sizeof(linebuf) - (pbuf-linebuf), "    ");
		cbuf = (char*)wbuf;
		for (i = 0; i < n*sizeof(uint32_t); i ++)
			pbuf += ocs_snprintf(pbuf, sizeof(linebuf) - (pbuf-linebuf), "%c", _isprint(cbuf[i]) ? cbuf[i] : '.');
		pbuf += ocs_snprintf(pbuf, sizeof(linebuf) - (pbuf-linebuf), "\n");

		ocs_log_debug(os, "%s", linebuf);

		wbuf += n;
		word_count -= n;
		addr += n*sizeof(uint32_t);
	}
}