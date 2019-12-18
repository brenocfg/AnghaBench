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
typedef  scalar_t__ uint8_t ;
typedef  unsigned int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 size_t BYTES2CHARS (size_t) ; 
 scalar_t__* encode64 (scalar_t__*,size_t,scalar_t__ const*,size_t) ; 
 scalar_t__* encode64_uint32 (scalar_t__*,size_t,int,int) ; 
 int /*<<< orphan*/ * itoa64 ; 

uint8_t *
escrypt_gensalt_r(uint32_t N_log2, uint32_t r, uint32_t p, const uint8_t *src,
                  size_t srclen, uint8_t *buf, size_t buflen)
{
    uint8_t *dst;
    size_t   prefixlen =
        (sizeof "$7$" - 1U) + (1U /* N_log2 */) + (5U /* r */) + (5U /* p */);
    size_t saltlen = BYTES2CHARS(srclen);
    size_t need;

    need = prefixlen + saltlen + 1;
    if (need > buflen || need < saltlen || saltlen < srclen) {
        return NULL; /* LCOV_EXCL_LINE */
    }
    if (N_log2 > 63 || ((uint64_t) r * (uint64_t) p >= (1U << 30))) {
        return NULL; /* LCOV_EXCL_LINE */
    }
    dst    = buf;
    *dst++ = '$';
    *dst++ = '7';
    *dst++ = '$';

    *dst++ = itoa64[N_log2];

    dst = encode64_uint32(dst, buflen - (dst - buf), r, 30);
    if (!dst) {
        return NULL; /* Can't happen LCOV_EXCL_LINE */
    }
    dst = encode64_uint32(dst, buflen - (dst - buf), p, 30);
    if (!dst) {
        return NULL; /* Can't happen LCOV_EXCL_LINE */
    }
    dst = encode64(dst, buflen - (dst - buf), src, srclen);
    if (!dst || dst >= buf + buflen) {
        return NULL; /* Can't happen LCOV_EXCL_LINE */
    }
    *dst = 0; /* NUL termination */

    return buf;
}