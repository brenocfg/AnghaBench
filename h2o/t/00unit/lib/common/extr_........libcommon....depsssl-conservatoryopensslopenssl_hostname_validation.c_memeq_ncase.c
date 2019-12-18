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
 scalar_t__ lowercase (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memeq_ncase(const char *x, const char *y, size_t l) {
	if (l == 0)
		return 1;
	do {
		if (lowercase(*x++) != lowercase(*y++))
			return 0;
	} while (--l != 0);
	return 1;
}