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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ldm_error (char*,...) ; 

__attribute__((used)) static int ldm_relative(const u8 *buffer, int buflen, int base, int offset)
{

	base += offset;
	if (!buffer || offset < 0 || base > buflen) {
		if (!buffer)
			ldm_error("!buffer");
		if (offset < 0)
			ldm_error("offset (%d) < 0", offset);
		if (base > buflen)
			ldm_error("base (%d) > buflen (%d)", base, buflen);
		return -1;
	}
	if (base + buffer[base] >= buflen) {
		ldm_error("base (%d) + buffer[base] (%d) >= buflen (%d)", base,
				buffer[base], buflen);
		return -1;
	}
	return buffer[base] + offset + 1;
}