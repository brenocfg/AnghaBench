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
 scalar_t__ hdr_sz (size_t*,unsigned char const**,unsigned char const*) ; 

int git_delta_read_header(
	size_t *base_out,
	size_t *result_out,
	const unsigned char *delta,
	size_t delta_len)
{
	const unsigned char *delta_end = delta + delta_len;
	if ((hdr_sz(base_out, &delta, delta_end) < 0) ||
		(hdr_sz(result_out, &delta, delta_end) < 0))
		return -1;
	return 0;
}