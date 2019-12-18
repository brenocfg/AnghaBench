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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_byte_to_hex (char*,int /*<<< orphan*/ ) ; 

char *quicly_escape_unsafe_string(char *buf, const void *bytes, size_t len)
{
    char *dst = buf;
    const char *src = bytes, *end = src + len;

    for (; src != end; ++src) {
        if (('0' <= *src && *src <= 0x7e) && !(*src == '"' || *src == '\'' || *src == '\\')) {
            *dst++ = *src;
        } else {
            *dst++ = '\\';
            *dst++ = 'x';
            quicly_byte_to_hex(dst, (uint8_t)*src);
        }
    }
    *dst = '\0';

    return buf;
}