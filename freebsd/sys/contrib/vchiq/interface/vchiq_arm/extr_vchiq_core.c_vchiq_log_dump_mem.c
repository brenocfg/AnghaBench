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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_LOG_TRACE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  vchiq_log_trace (int /*<<< orphan*/ ,char*,char const*,char*,...) ; 

void vchiq_log_dump_mem(const char *label, uint32_t addr, const void *voidMem,
	size_t numBytes)
{
	const uint8_t  *mem = (const uint8_t *)voidMem;
	size_t          offset;
	char            lineBuf[100];
	char           *s;

	while (numBytes > 0) {
		s = lineBuf;

		for (offset = 0; offset < 16; offset++) {
			if (offset < numBytes)
				s += snprintf(s, 4, "%02x ", mem[offset]);
			else
				s += snprintf(s, 4, "   ");
		}

		for (offset = 0; offset < 16; offset++) {
			if (offset < numBytes) {
				uint8_t ch = mem[offset];

				if ((ch < ' ') || (ch > '~'))
					ch = '.';
				*s++ = (char)ch;
			}
		}
		*s++ = '\0';

		if ((label != NULL) && (*label != '\0'))
			vchiq_log_trace(VCHIQ_LOG_TRACE,
				"%s: %08x: %s", label, addr, lineBuf);
		else
			vchiq_log_trace(VCHIQ_LOG_TRACE,
				"%08x: %s", addr, lineBuf);

		addr += 16;
		mem += 16;
		if (numBytes > 16)
			numBytes -= 16;
		else
			numBytes = 0;
	}
}