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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static inline int pa_pxp_offset_valid(u8 bus, u8 devfn, int offset)
{
	/* Device 0 Function 0 is special: It's config space spans function 1 as
	 * well, so allow larger offset. It's really a two-function device but the
	 * second function does not probe.
	 */
	if (bus == 0 && devfn == 0)
		return offset < 8192;
	else
		return offset < 4096;
}