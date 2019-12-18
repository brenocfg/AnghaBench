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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  symlink_len (int /*<<< orphan*/  const*,char const*,size_t) ; 

__attribute__((used)) static void
symlink_long(const atf_tc_t *tc, const char *mp)
{
	/*
	 * Test lengths close to powers of two, as those are likely
	 * to be edge cases.
	 */
	size_t len;
	int fuzz;
	for (len = 2; len <= 65536; len *= 2) {
		for (fuzz = -1; fuzz <= 1; fuzz++) {
			symlink_len(tc, mp, len + fuzz);
		}
	}
}