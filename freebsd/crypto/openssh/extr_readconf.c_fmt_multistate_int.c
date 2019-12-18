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
typedef  size_t u_int ;
struct multistate {char const* key; int value; } ;

/* Variables and functions */

__attribute__((used)) static const char *
fmt_multistate_int(int val, const struct multistate *m)
{
	u_int i;

	for (i = 0; m[i].key != NULL; i++) {
		if (m[i].value == val)
			return m[i].key;
	}
	return "UNKNOWN";
}