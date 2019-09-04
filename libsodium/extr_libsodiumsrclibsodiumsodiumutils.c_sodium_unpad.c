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

int
sodium_unpad(size_t *unpadded_buflen_p, const unsigned char *buf,
             size_t padded_buflen, size_t blocksize)
{
    const unsigned char *tail;
    unsigned char        acc = 0U;
    unsigned char        c;
    unsigned char        valid = 0U;
    volatile size_t      pad_len = 0U;
    size_t               i;
    size_t               is_barrier;

    if (padded_buflen < blocksize || blocksize <= 0U) {
        return -1;
    }
    tail = &buf[padded_buflen - 1U];

    for (i = 0U; i < blocksize; i++) {
        c = *(tail - i);
        is_barrier =
            (( (acc - 1U) & (pad_len - 1U) & ((c ^ 0x80) - 1U) ) >> 8) & 1U;
        acc |= c;
        pad_len |= i & (1U + ~is_barrier);
        valid |= (unsigned char) is_barrier;
    }
    *unpadded_buflen_p = padded_buflen - 1U - pad_len;

    return (int) (valid - 1U);
}