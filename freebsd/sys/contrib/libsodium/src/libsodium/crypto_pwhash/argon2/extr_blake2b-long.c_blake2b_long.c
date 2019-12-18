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
typedef  unsigned char const uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  outlen_bytes ;
typedef  int /*<<< orphan*/  crypto_generichash_blake2b_state ;
typedef  int /*<<< orphan*/  blake_state ;

/* Variables and functions */
 int /*<<< orphan*/  STORE32_LE (unsigned char const*,size_t) ; 
 int /*<<< orphan*/  TRY (int /*<<< orphan*/ ) ; 
 size_t UINT32_MAX ; 
 int /*<<< orphan*/  crypto_generichash_blake2b (unsigned char const*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ *,unsigned int) ; 
 size_t crypto_generichash_blake2b_BYTES_MAX ; 
 int /*<<< orphan*/  crypto_generichash_blake2b_final (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  crypto_generichash_blake2b_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,size_t) ; 
 int /*<<< orphan*/  crypto_generichash_blake2b_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sodium_memzero (int /*<<< orphan*/ *,int) ; 

int
blake2b_long(void *pout, size_t outlen, const void *in, size_t inlen)
{
    uint8_t *out = (uint8_t *) pout;
    crypto_generichash_blake2b_state blake_state;
    uint8_t outlen_bytes[4 /* sizeof(uint32_t) */] = { 0 };
    int     ret = -1;

    if (outlen > UINT32_MAX) {
        goto fail; /* LCOV_EXCL_LINE */
    }

    /* Ensure little-endian byte order! */
    STORE32_LE(outlen_bytes, (uint32_t) outlen);

#define TRY(statement)   \
    do {                 \
        ret = statement; \
        if (ret < 0) {   \
            goto fail;   \
        }                \
    } while ((void) 0, 0)

    if (outlen <= crypto_generichash_blake2b_BYTES_MAX) {
        TRY(crypto_generichash_blake2b_init(&blake_state, NULL, 0U, outlen));
        TRY(crypto_generichash_blake2b_update(&blake_state, outlen_bytes,
                                              sizeof(outlen_bytes)));
        TRY(crypto_generichash_blake2b_update(
            &blake_state, (const unsigned char *) in, inlen));
        TRY(crypto_generichash_blake2b_final(&blake_state, out, outlen));
    } else {
        uint32_t toproduce;
        uint8_t  out_buffer[crypto_generichash_blake2b_BYTES_MAX];
        uint8_t  in_buffer[crypto_generichash_blake2b_BYTES_MAX];
        TRY(crypto_generichash_blake2b_init(
            &blake_state, NULL, 0U, crypto_generichash_blake2b_BYTES_MAX));
        TRY(crypto_generichash_blake2b_update(&blake_state, outlen_bytes,
                                              sizeof(outlen_bytes)));
        TRY(crypto_generichash_blake2b_update(
            &blake_state, (const unsigned char *) in, inlen));
        TRY(crypto_generichash_blake2b_final(
            &blake_state, out_buffer, crypto_generichash_blake2b_BYTES_MAX));
        memcpy(out, out_buffer, crypto_generichash_blake2b_BYTES_MAX / 2);
        out += crypto_generichash_blake2b_BYTES_MAX / 2;
        toproduce =
            (uint32_t) outlen - crypto_generichash_blake2b_BYTES_MAX / 2;

        while (toproduce > crypto_generichash_blake2b_BYTES_MAX) {
            memcpy(in_buffer, out_buffer, crypto_generichash_blake2b_BYTES_MAX);
            TRY(crypto_generichash_blake2b(
                out_buffer, crypto_generichash_blake2b_BYTES_MAX, in_buffer,
                crypto_generichash_blake2b_BYTES_MAX, NULL, 0U));
            memcpy(out, out_buffer, crypto_generichash_blake2b_BYTES_MAX / 2);
            out += crypto_generichash_blake2b_BYTES_MAX / 2;
            toproduce -= crypto_generichash_blake2b_BYTES_MAX / 2;
        }

        memcpy(in_buffer, out_buffer, crypto_generichash_blake2b_BYTES_MAX);
        TRY(crypto_generichash_blake2b(out_buffer, toproduce, in_buffer,
                                       crypto_generichash_blake2b_BYTES_MAX,
                                       NULL, 0U));
        memcpy(out, out_buffer, toproduce);
    }
fail:
    sodium_memzero(&blake_state, sizeof(blake_state));
    return ret;
#undef TRY
}