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
typedef  char uint8_t ;
typedef  char uint32_t ;

/* Variables and functions */
 char* b64_decoding_table ; 

const char*
base64_decode(const uint32_t *src, size_t src_sz, uint8_t *dest, size_t dest_capacity, size_t *dest_sz) {
    if (!src_sz) { *dest_sz = 0; return NULL; }
    if (src_sz % 4 != 0) return "base64 encoded data must have a length that is a multiple of four";
    *dest_sz = (src_sz / 4) * 3;
    if (src[src_sz - 1] == '=') (*dest_sz)--;
    if (src[src_sz - 2] == '=') (*dest_sz)--;
    if (*dest_sz > dest_capacity) return "output buffer too small";
    for (size_t i = 0, j = 0; i < src_sz;) {
        uint32_t sextet_a = src[i] == '=' ? 0 & i++ : b64_decoding_table[src[i++] & 0xff];
        uint32_t sextet_b = src[i] == '=' ? 0 & i++ : b64_decoding_table[src[i++] & 0xff];
        uint32_t sextet_c = src[i] == '=' ? 0 & i++ : b64_decoding_table[src[i++] & 0xff];
        uint32_t sextet_d = src[i] == '=' ? 0 & i++ : b64_decoding_table[src[i++] & 0xff];
        uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

        if (j < *dest_sz) dest[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *dest_sz) dest[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *dest_sz) dest[j++] = (triple >> 0 * 8) & 0xFF;
    }
    return NULL;
}