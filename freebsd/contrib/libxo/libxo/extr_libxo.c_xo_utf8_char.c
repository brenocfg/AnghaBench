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
typedef  unsigned char wchar_t ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned char const* xo_utf8_data_bits ; 

__attribute__((used)) static inline wchar_t
xo_utf8_char (const char *buf, ssize_t len)
{
    /* Most common case: singleton byte */
    if (len == 1)
	return (unsigned char) buf[0];

    ssize_t i;
    wchar_t wc;
    const unsigned char *cp = (const unsigned char *) buf;

    wc = *cp & xo_utf8_data_bits[len];
    for (i = 1; i < len; i++) {
	wc <<= 6;		/* Low six bits have data */
	wc |= cp[i] & 0x3f;
	if ((cp[i] & 0xc0) != 0x80)
	    return (wchar_t) -1;
    }

    return wc;
}