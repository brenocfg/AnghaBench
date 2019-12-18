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

/* Variables and functions */
 int /*<<< orphan*/  trace_pack ; 
 int /*<<< orphan*/  trace_verbatim (int /*<<< orphan*/ *,char const*,unsigned int) ; 

__attribute__((used)) static int packet_trace_pack(const char *buf, unsigned int len, int sideband)
{
	if (!sideband) {
		trace_verbatim(&trace_pack, buf, len);
		return 1;
	} else if (len && *buf == '\1') {
		trace_verbatim(&trace_pack, buf + 1, len - 1);
		return 1;
	} else {
		/* it's another non-pack sideband */
		return 0;
	}
}