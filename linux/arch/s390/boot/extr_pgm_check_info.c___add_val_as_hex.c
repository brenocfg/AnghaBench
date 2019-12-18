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
 char* hex_byte_pack (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *__add_val_as_hex(char *dst, const unsigned char *src, size_t count)
{
	while (count--)
		dst = hex_byte_pack(dst, *src++);
	return dst;
}