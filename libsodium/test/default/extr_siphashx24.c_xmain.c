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
 int MAXLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int crypto_shorthash_siphash24_BYTES ; 
 int crypto_shorthash_siphash24_KEYBYTES ; 
 int /*<<< orphan*/  crypto_shorthash_siphashx24 (unsigned char*,unsigned char*,unsigned long long,unsigned char*) ; 
 int crypto_shorthash_siphashx24_BYTES ; 
 int crypto_shorthash_siphashx24_KEYBYTES ; 
 int crypto_shorthash_siphashx24_bytes () ; 
 int crypto_shorthash_siphashx24_keybytes () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
main(void)
{
    unsigned char in[MAXLEN];
    unsigned char out[crypto_shorthash_siphashx24_BYTES];
    unsigned char k[crypto_shorthash_siphashx24_KEYBYTES];
    size_t        i;
    size_t        j;

    for (i = 0; i < crypto_shorthash_siphashx24_KEYBYTES; ++i) {
        k[i] = (unsigned char) i;
    }
    for (i = 0; i < MAXLEN; ++i) {
        in[i] = (unsigned char) i;
        crypto_shorthash_siphashx24(out, in, (unsigned long long) i, k);
        for (j = 0; j < crypto_shorthash_siphashx24_BYTES; ++j) {
            printf("%02x", (unsigned int) out[j]);
        }
        printf("\n");
    }
    assert(crypto_shorthash_siphashx24_KEYBYTES >= crypto_shorthash_siphash24_KEYBYTES);
    assert(crypto_shorthash_siphashx24_BYTES > crypto_shorthash_siphash24_BYTES);
    assert(crypto_shorthash_siphashx24_bytes() == crypto_shorthash_siphashx24_BYTES);
    assert(crypto_shorthash_siphashx24_keybytes() == crypto_shorthash_siphashx24_KEYBYTES);

    return 0;
}