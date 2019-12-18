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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  quicly_byte_to_hex (char*,size_t const) ; 

char *quicly_hexdump(const uint8_t *bytes, size_t len, size_t indent)
{
    size_t i, line, row, bufsize = indent == SIZE_MAX ? len * 2 + 1 : (indent + 5 + 3 * 16 + 2 + 16 + 1) * ((len + 15) / 16) + 1;
    char *buf, *p;

    if ((buf = malloc(bufsize)) == NULL)
        return NULL;
    p = buf;
    if (indent == SIZE_MAX) {
        for (i = 0; i != len; ++i) {
            quicly_byte_to_hex(p, bytes[i]);
            p += 2;
        }
    } else {
        for (line = 0; line * 16 < len; ++line) {
            for (i = 0; i < indent; ++i)
                *p++ = ' ';
            quicly_byte_to_hex(p, (line >> 4) & 0xff);
            p += 2;
            quicly_byte_to_hex(p, (line << 4) & 0xff);
            p += 2;
            *p++ = ' ';
            for (row = 0; row < 16; ++row) {
                *p++ = row == 8 ? '-' : ' ';
                if (line * 16 + row < len) {
                    quicly_byte_to_hex(p, bytes[line * 16 + row]);
                    p += 2;
                } else {
                    *p++ = ' ';
                    *p++ = ' ';
                }
            }
            *p++ = ' ';
            *p++ = ' ';
            for (row = 0; row < 16; ++row) {
                if (line * 16 + row < len) {
                    int ch = bytes[line * 16 + row];
                    *p++ = 0x20 <= ch && ch < 0x7f ? ch : '.';
                } else {
                    *p++ = ' ';
                }
            }
            *p++ = '\n';
        }
    }
    *p++ = '\0';

    assert(p - buf <= bufsize);

    return buf;
}