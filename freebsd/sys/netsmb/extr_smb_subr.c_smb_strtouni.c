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
typedef  scalar_t__ u_int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 

void
smb_strtouni(u_int16_t *dst, const char *src)
{
	while (*src) {
		*dst++ = htole16(*src++);
	}
	*dst = 0;
}