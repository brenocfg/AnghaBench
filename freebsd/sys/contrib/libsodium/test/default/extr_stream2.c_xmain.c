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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crypto_hash_sha256 (int*,scalar_t__*,int) ; 
 int /*<<< orphan*/  crypto_stream_salsa20 (scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crypto_stream_salsa20_keybytes () ; 
 unsigned int crypto_stream_salsa20_messagebytes_max () ; 
 unsigned int crypto_stream_salsa20_noncebytes () ; 
 int /*<<< orphan*/  crypto_stream_salsa20_xor_ic (scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int* h ; 
 int /*<<< orphan*/  noncesuffix ; 
 scalar_t__* output ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  secondkey ; 

int
main(void)
{
    int i;
    crypto_stream_salsa20(output, sizeof output, noncesuffix, secondkey);
    crypto_hash_sha256(h, output, sizeof output);
    for (i = 0; i < 32; ++i)
        printf("%02x", h[i]);
    printf("\n");

    assert(sizeof output > 4000);

    crypto_stream_salsa20_xor_ic(output, output, 4000, noncesuffix, 0U,
                                 secondkey);
    for (i = 0; i < 4000; ++i)
        assert(output[i] == 0);

    crypto_stream_salsa20_xor_ic(output, output, 4000, noncesuffix, 1U,
                                 secondkey);
    crypto_hash_sha256(h, output, sizeof output);
    for (i = 0; i < 32; ++i)
        printf("%02x", h[i]);
    printf("\n");

    assert(crypto_stream_salsa20_keybytes() > 0U);
    assert(crypto_stream_salsa20_noncebytes() > 0U);
    assert(crypto_stream_salsa20_messagebytes_max() > 0U);

    return 0;
}