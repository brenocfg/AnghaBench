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
typedef  int efi_char ;

/* Variables and functions */

__attribute__((used)) static size_t
utf8_len_of_ucs2(const efi_char *nm)
{
	size_t len;
	efi_char c;

	len = 0;
	while (*nm) {
		c = *nm++;
		if (c > 0x7ff)
			len += 3;
		else if (c > 0x7f)
			len += 2;
		else
			len++;
	}

	return (len);
}