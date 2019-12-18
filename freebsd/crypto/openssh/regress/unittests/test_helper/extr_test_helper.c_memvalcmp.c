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
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ const u_char ;

/* Variables and functions */

__attribute__((used)) static int
memvalcmp(const u_int8_t *s, u_char v, size_t l, size_t *where)
{
	size_t i;

	for (i = 0; i < l; i++) {
		if (s[i] != v) {
			*where = i;
			return 1;
		}
	}
	return 0;
}