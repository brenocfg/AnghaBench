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

char *
hexdigest(char *buf, size_t bufsz, unsigned char *foo, size_t foo_len)
{
	char const hex2ascii[] = "0123456789abcdef";
	size_t i;

	/* every binary byte is 2 chars in hex + newline + null  */
	if (bufsz < (2 * foo_len) + 2)
		return (NULL);

	for (i = 0; i < foo_len; i++) {
		buf[i * 2] = hex2ascii[foo[i] >> 4];
		buf[i * 2 + 1] = hex2ascii[foo[i] & 0x0f];
	}

	buf[i * 2] = 0x0A; /* we also want a newline */
	buf[i * 2 + 1] = '\0';

	return (buf);
}