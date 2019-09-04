#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  in_hex; int /*<<< orphan*/  out_hex; int /*<<< orphan*/  key_hex; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crypto_generichash (unsigned char*,int,unsigned char*,unsigned long long,unsigned char*,int) ; 
 int crypto_generichash_BYTES_MAX ; 
 int crypto_generichash_KEYBYTES_MAX ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 int /*<<< orphan*/  sodium_hex2bin (unsigned char*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sodium_malloc (size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 TYPE_1__* tests ; 

__attribute__((used)) static int
tv(void)
{
    unsigned char *expected_out;
    unsigned char *in;
    unsigned char *key;
    unsigned char *out;
    size_t         i = 0U;
    size_t         in_len;

    key = (unsigned char *) sodium_malloc(crypto_generichash_KEYBYTES_MAX);
    out = (unsigned char *) sodium_malloc(crypto_generichash_BYTES_MAX);
    expected_out = (unsigned char *) sodium_malloc(crypto_generichash_BYTES_MAX);
    do {
        assert(strlen(tests[i].key_hex) == 2 * crypto_generichash_KEYBYTES_MAX);
        sodium_hex2bin(key, crypto_generichash_KEYBYTES_MAX,
                       tests[i].key_hex, strlen(tests[i].key_hex),
                       NULL, NULL, NULL);
        assert(strlen(tests[i].out_hex) == 2 * crypto_generichash_BYTES_MAX);
        sodium_hex2bin(expected_out, crypto_generichash_BYTES_MAX,
                       tests[i].out_hex, strlen(tests[i].out_hex),
                       NULL, NULL, NULL);
        in_len = strlen(tests[i].in_hex) / 2;
        in = (unsigned char *) sodium_malloc(in_len);
        sodium_hex2bin(in, in_len, tests[i].in_hex, strlen(tests[i].in_hex),
                       NULL, NULL, NULL);
        crypto_generichash(out, crypto_generichash_BYTES_MAX,
                           in, (unsigned long long) in_len,
                           key, crypto_generichash_KEYBYTES_MAX);
        if (memcmp(out, expected_out, crypto_generichash_BYTES_MAX) != 0) {
            printf("Test vector #%u failed\n", (unsigned int) i);
        }
        sodium_free(in);
    } while (++i < (sizeof tests) / (sizeof tests[0]));
    sodium_free(key);
    sodium_free(out);
    sodium_free(expected_out);

    return 0;
}