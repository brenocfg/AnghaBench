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
 int /*<<< orphan*/ * ascii64 ; 

__attribute__((used)) static char*
__md5_to64(char *s, unsigned v, int n)
{
	while (--n >= 0) {
		*s++ = ascii64[v & 0x3f];
		v >>= 6;
	}
	return s;
}