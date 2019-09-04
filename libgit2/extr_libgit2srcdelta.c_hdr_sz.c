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
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hdr_sz(
	size_t *size,
	const unsigned char **delta,
	const unsigned char *end)
{
	const unsigned char *d = *delta;
	size_t r = 0;
	unsigned int c, shift = 0;

	do {
		if (d == end) {
			git_error_set(GIT_ERROR_INVALID, "truncated delta");
			return -1;
		}

		c = *d++;
		r |= (c & 0x7f) << shift;
		shift += 7;
	} while (c & 0x80);
	*delta = d;
	*size = r;
	return 0;
}