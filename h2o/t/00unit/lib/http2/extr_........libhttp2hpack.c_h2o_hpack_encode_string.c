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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ H2O_LIKELY (int) ; 
 size_t SIZE_MAX ; 
 size_t encode_as_is (char*,char const*,size_t) ; 
 int encode_int_is_onebyte (int /*<<< orphan*/ ,int) ; 
 size_t h2o_hpack_encode_huffman (char*,char const*,size_t) ; 
 char* h2o_hpack_encode_int (char*,size_t,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 

size_t h2o_hpack_encode_string(uint8_t *dst, const char *s, size_t len)
{
    if (H2O_LIKELY(len != 0)) {
        /* try to encode using huffman */
        size_t hufflen = h2o_hpack_encode_huffman(dst + 1, (const uint8_t *)s, len);
        if (H2O_LIKELY(hufflen != SIZE_MAX)) {
            size_t head_len;
            if (H2O_LIKELY(encode_int_is_onebyte((uint32_t)hufflen, 7))) {
                dst[0] = (uint8_t)(0x80 | hufflen);
                head_len = 1;
            } else {
                uint8_t head[8];
                head[0] = '\x80';
                head_len = h2o_hpack_encode_int(head, hufflen, 7) - head;
                memmove(dst + head_len, dst + 1, hufflen);
                memcpy(dst, head, head_len);
            }
            return head_len + hufflen;
        }
    }
    return encode_as_is(dst, s, len);
}