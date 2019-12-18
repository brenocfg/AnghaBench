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
typedef  int wchar_t ;
typedef  int ssize_t ;

/* Variables and functions */
 char* xo_utf8_data_bits ; 
 char* xo_utf8_len_bits ; 

__attribute__((used)) static void
xo_utf8_emit_char (char *buf, ssize_t len, wchar_t wc)
{
    ssize_t i;

    if (len == 1) { /* Simple case */
	buf[0] = wc & 0x7f;
	return;
    }

    /* Start with the low bits and insert them, six bits at a time */
    for (i = len - 1; i >= 0; i--) {
	buf[i] = 0x80 | (wc & 0x3f);
	wc >>= 6;		/* Drop the low six bits */
    }

    /* Finish off the first byte with the length bits */
    buf[0] &= xo_utf8_data_bits[len]; /* Clear out the length bits */
    buf[0] |= xo_utf8_len_bits[len]; /* Drop in new length bits */
}