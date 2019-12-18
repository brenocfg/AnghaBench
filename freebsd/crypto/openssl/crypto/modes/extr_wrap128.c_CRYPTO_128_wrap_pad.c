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
typedef  int /*<<< orphan*/  (* block128_f ) (unsigned char*,unsigned char*,void*) ;

/* Variables and functions */
 size_t CRYPTO128_WRAP_MAX ; 
 int CRYPTO_128_wrap (void*,unsigned char*,unsigned char*,unsigned char*,size_t const,int /*<<< orphan*/  (*) (unsigned char*,unsigned char*,void*)) ; 
 unsigned char* default_aiv ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t const) ; 

size_t CRYPTO_128_wrap_pad(void *key, const unsigned char *icv,
                           unsigned char *out,
                           const unsigned char *in, size_t inlen,
                           block128_f block)
{
    /* n: number of 64-bit blocks in the padded key data
     *
     * If length of plain text is not a multiple of 8, pad the plain text octet
     * string on the right with octets of zeros, where final length is the
     * smallest multiple of 8 that is greater than length of plain text.
     * If length of plain text is a multiple of 8, then there is no padding. */
    const size_t blocks_padded = (inlen + 7) / 8; /* CEILING(m/8) */
    const size_t padded_len = blocks_padded * 8;
    const size_t padding_len = padded_len - inlen;
    /* RFC 5649 section 3: Alternative Initial Value */
    unsigned char aiv[8];
    int ret;

    /* Section 1: use 32-bit fixed field for plaintext octet length */
    if (inlen == 0 || inlen >= CRYPTO128_WRAP_MAX)
        return 0;

    /* Section 3: Alternative Initial Value */
    if (!icv)
        memcpy(aiv, default_aiv, 4);
    else
        memcpy(aiv, icv, 4);    /* Standard doesn't mention this. */

    aiv[4] = (inlen >> 24) & 0xFF;
    aiv[5] = (inlen >> 16) & 0xFF;
    aiv[6] = (inlen >> 8) & 0xFF;
    aiv[7] = inlen & 0xFF;

    if (padded_len == 8) {
        /*
         * Section 4.1 - special case in step 2: If the padded plaintext
         * contains exactly eight octets, then prepend the AIV and encrypt
         * the resulting 128-bit block using AES in ECB mode.
         */
        memmove(out + 8, in, inlen);
        memcpy(out, aiv, 8);
        memset(out + 8 + inlen, 0, padding_len);
        block(out, out, key);
        ret = 16;               /* AIV + padded input */
    } else {
        memmove(out, in, inlen);
        memset(out + inlen, 0, padding_len); /* Section 4.1 step 1 */
        ret = CRYPTO_128_wrap(key, aiv, out, out, padded_len, block);
    }

    return ret;
}