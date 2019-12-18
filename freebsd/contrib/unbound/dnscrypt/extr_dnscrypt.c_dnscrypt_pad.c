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
typedef  size_t const uint32_t ;
typedef  int /*<<< orphan*/  rnd ;

/* Variables and functions */
 size_t DNSCRYPT_BLOCK_SIZE ; 
 size_t const DNSCRYPT_MIN_PAD_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t crypto_box_HALF_NONCEBYTES ; 
 int /*<<< orphan*/  crypto_stream (unsigned char*,unsigned long long,scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

size_t
dnscrypt_pad(uint8_t *buf, const size_t len, const size_t max_len,
             const uint8_t *nonce, const uint8_t *secretkey)
{
    uint8_t *buf_padding_area = buf + len;
    size_t padded_len;
    uint32_t rnd;

    // no padding
    if (max_len < len + DNSCRYPT_MIN_PAD_LEN)
        return len;

    assert(nonce[crypto_box_HALF_NONCEBYTES] == nonce[0]);

    crypto_stream((unsigned char *)&rnd, (unsigned long long)sizeof(rnd), nonce,
                  secretkey);
    padded_len =
        len + DNSCRYPT_MIN_PAD_LEN + rnd % (max_len - len -
                                            DNSCRYPT_MIN_PAD_LEN + 1);
    padded_len += DNSCRYPT_BLOCK_SIZE - padded_len % DNSCRYPT_BLOCK_SIZE;
    if (padded_len > max_len)
        padded_len = max_len;

    memset(buf_padding_area, 0, padded_len - len);
    *buf_padding_area = 0x80;

    return padded_len;
}