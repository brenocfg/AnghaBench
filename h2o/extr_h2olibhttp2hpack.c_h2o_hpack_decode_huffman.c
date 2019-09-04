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
typedef  int uint8_t ;

/* Variables and functions */
 int NGHTTP2_HUFF_INVALID_FOR_HEADER_NAME ; 
 int NGHTTP2_HUFF_INVALID_FOR_HEADER_VALUE ; 
 int NGHTTP2_HUFF_UPPER_CASE_CHAR ; 
 size_t SIZE_MAX ; 
 char* h2o_hpack_err_found_upper_case_in_header_name ; 
 char* h2o_hpack_soft_err_found_invalid_char_in_header_name ; 
 char* h2o_hpack_soft_err_found_invalid_char_in_header_value ; 
 char* huffdecode4 (char*,int const,int*,int*,int*) ; 

size_t h2o_hpack_decode_huffman(char *_dst, const uint8_t *src, size_t len, int is_name, const char **err_desc)
{
    char *dst = _dst;
    const uint8_t *src_end = src + len;
    uint8_t state = 0, seen_char_types = 0;
    int maybe_eos = 1;

    /* decode */
    for (; src < src_end; src++) {
        if ((dst = huffdecode4(dst, *src >> 4, &state, &maybe_eos, &seen_char_types)) == NULL)
            return SIZE_MAX;
        if ((dst = huffdecode4(dst, *src & 0xf, &state, &maybe_eos, &seen_char_types)) == NULL)
            return SIZE_MAX;
    }
    if (!maybe_eos)
        return SIZE_MAX;

    /* validate */
    if (is_name) {
        if (dst == _dst)
            return SIZE_MAX;
        /* pseudo-headers are checked later in `decode_header` */
        if ((seen_char_types & NGHTTP2_HUFF_INVALID_FOR_HEADER_NAME) != 0 && _dst[0] != ':') {
            if ((seen_char_types & NGHTTP2_HUFF_UPPER_CASE_CHAR) != 0) {
                *err_desc = h2o_hpack_err_found_upper_case_in_header_name;
                return SIZE_MAX;
            } else {
                *err_desc = h2o_hpack_soft_err_found_invalid_char_in_header_name;
            }
        }
    } else {
        if ((seen_char_types & NGHTTP2_HUFF_INVALID_FOR_HEADER_VALUE) != 0)
            *err_desc = h2o_hpack_soft_err_found_invalid_char_in_header_value;
    }

    return dst - _dst;
}