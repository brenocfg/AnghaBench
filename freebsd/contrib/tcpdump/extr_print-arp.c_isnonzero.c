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
typedef  scalar_t__ u_char ;

/* Variables and functions */

__attribute__((used)) static int
isnonzero(const u_char *a, size_t len)
{
	while (len > 0) {
		if (*a != 0)
			return (1);
		a++;
		len--;
	}
	return (0);
}