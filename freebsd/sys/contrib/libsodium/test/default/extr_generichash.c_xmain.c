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
 int crypto_generichash (unsigned char*,unsigned long long,unsigned char*,unsigned long long,unsigned char*,int) ; 
 int crypto_generichash_BYTES_MAX ; 
 int crypto_generichash_KEYBYTES_MAX ; 
 unsigned int crypto_generichash_blake2b_bytes () ; 
 unsigned int crypto_generichash_blake2b_bytes_max () ; 
 unsigned int crypto_generichash_blake2b_bytes_min () ; 
 unsigned int crypto_generichash_blake2b_keybytes () ; 
 unsigned int crypto_generichash_blake2b_keybytes_max () ; 
 unsigned int crypto_generichash_blake2b_keybytes_min () ; 
 unsigned int crypto_generichash_blake2b_personalbytes () ; 
 unsigned int crypto_generichash_blake2b_saltbytes () ; 
 unsigned int crypto_generichash_bytes () ; 
 unsigned int crypto_generichash_bytes_max () ; 
 unsigned int crypto_generichash_bytes_min () ; 
 unsigned int crypto_generichash_keybytes () ; 
 unsigned int crypto_generichash_keybytes_max () ; 
 unsigned int crypto_generichash_keybytes_min () ; 
 int /*<<< orphan*/  crypto_generichash_primitive () ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tv () ; 

int
main(void)
{
    unsigned char in[MAXLEN];
    unsigned char out[crypto_generichash_BYTES_MAX];
    unsigned char k[crypto_generichash_KEYBYTES_MAX];
    size_t        h;
    size_t        i;
    size_t        j;

    tv();

    for (h = 0; h < crypto_generichash_KEYBYTES_MAX; ++h) {
        k[h] = (unsigned char) h;
    }

    for (i = 0; i < MAXLEN; ++i) {
        in[i] = (unsigned char) i;
        crypto_generichash(out, 1 + i % crypto_generichash_BYTES_MAX, in,
                           (unsigned long long) i, k,
                           1 + i % crypto_generichash_KEYBYTES_MAX);
        for (j = 0; j < 1 + i % crypto_generichash_BYTES_MAX; ++j) {
            printf("%02x", (unsigned int) out[j]);
        }
        printf("\n");
    }

    memset(out, 0, sizeof out);
    crypto_generichash(out, crypto_generichash_BYTES_MAX, in,
                       (unsigned long long) i, k, 0U);
    for (j = 0; j < crypto_generichash_BYTES_MAX; ++j) {
        printf("%02x", (unsigned int) out[j]);
    }
    printf("\n");

    assert(crypto_generichash(NULL, 0,
                              in, (unsigned long long) sizeof in,
                              k, sizeof k) == -1);
    assert(crypto_generichash(NULL, crypto_generichash_BYTES_MAX + 1,
                              in, (unsigned long long) sizeof in,
                              k, sizeof k) == -1);
    assert(crypto_generichash(NULL, (unsigned long long) sizeof in,
                              in, (unsigned long long) sizeof in,
                              k, crypto_generichash_KEYBYTES_MAX + 1) == -1);

    assert(crypto_generichash_bytes_min() > 0U);
    assert(crypto_generichash_bytes_max() > 0U);
    assert(crypto_generichash_bytes() > 0U);
    assert(crypto_generichash_bytes() >= crypto_generichash_bytes_min());
    assert(crypto_generichash_bytes() <= crypto_generichash_bytes_max());
    assert(crypto_generichash_keybytes_min() > 0U);
    assert(crypto_generichash_keybytes_max() > 0U);
    assert(crypto_generichash_keybytes() > 0U);
    assert(crypto_generichash_keybytes() >= crypto_generichash_keybytes_min());
    assert(crypto_generichash_keybytes() <= crypto_generichash_keybytes_max());
    assert(strcmp(crypto_generichash_primitive(), "blake2b") == 0);
    assert(crypto_generichash_bytes_min()
           == crypto_generichash_blake2b_bytes_min());
    assert(crypto_generichash_bytes_max()
           == crypto_generichash_blake2b_bytes_max());
    assert(crypto_generichash_bytes() == crypto_generichash_blake2b_bytes());
    assert(crypto_generichash_keybytes_min()
           == crypto_generichash_blake2b_keybytes_min());
    assert(crypto_generichash_keybytes_max()
           == crypto_generichash_blake2b_keybytes_max());
    assert(crypto_generichash_keybytes()
           == crypto_generichash_blake2b_keybytes());
    assert(crypto_generichash_blake2b_saltbytes() > 0U);
    assert(crypto_generichash_blake2b_personalbytes() > 0U);

    return 0;
}