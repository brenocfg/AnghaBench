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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static void
digest2string(const uint8_t *digest, char *string, size_t len)
{
	while (len--) {
		if (*digest / 16 < 10)
			*string++ = '0' + *digest / 16;
		else
			*string++ = 'a' + *digest / 16 - 10;
		if (*digest % 16 < 10)
			*string++ = '0' + *digest % 16;
		else
			*string++ = 'a' + *digest % 16 - 10;
		++digest;
	}
	*string = '\0';
}