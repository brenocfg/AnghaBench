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
 size_t SIZE_MAX ; 
 size_t h2o_hpack_decode_huffman (char*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  h2o_hpack_validate_header_value (void*,size_t,char const**) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static size_t decode_value(int is_huff, const uint8_t *src, size_t srclen, char *outbuf, const char **err_desc)
{
    size_t outlen;

    if (is_huff) {
        if ((outlen = h2o_hpack_decode_huffman(outbuf, src, srclen, 0, err_desc)) == SIZE_MAX)
            return SIZE_MAX;
    } else {
        h2o_hpack_validate_header_value((void *)src, srclen, err_desc);
        memcpy(outbuf, src, srclen);
        outlen = srclen;
    }
    outbuf[outlen] = '\0';

    return outlen;
}