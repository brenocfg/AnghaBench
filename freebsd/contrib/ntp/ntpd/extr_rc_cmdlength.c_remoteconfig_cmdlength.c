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

size_t
remoteconfig_cmdlength(
	const char *src_buf,
	const char *src_end
	)
{
	const char *scan;
	unsigned char ch;

	/* trim whitespace & garbage from the right */
	while (src_end != src_buf) {
		ch = src_end[-1];
		if (ch > ' ' && ch < 128)
			break;
		--src_end;
	}
	/* now do a forward scan */
	for (scan = src_buf; scan != src_end; ++scan) {
		ch = scan[0];
		if ((ch < ' ' || ch >= 128) && ch != '\t')
			break;
	}
	return (size_t)(scan - src_buf);
}