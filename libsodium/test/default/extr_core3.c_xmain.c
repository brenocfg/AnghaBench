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
 int /*<<< orphan*/  C ; 
 int /*<<< orphan*/  NONCESUFFIX ; 
 int /*<<< orphan*/  SECONDKEY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crypto_core_salsa20 (unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_salsa2012 (unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_salsa208 (unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_core_salsa20_CONSTBYTES ; 
 scalar_t__ crypto_core_salsa20_INPUTBYTES ; 
 scalar_t__ crypto_core_salsa20_KEYBYTES ; 
 scalar_t__ crypto_core_salsa20_OUTPUTBYTES ; 
 scalar_t__ crypto_core_salsa20_constbytes () ; 
 scalar_t__ crypto_core_salsa20_inputbytes () ; 
 scalar_t__ crypto_core_salsa20_keybytes () ; 
 scalar_t__ crypto_core_salsa20_outputbytes () ; 
 int /*<<< orphan*/  crypto_hash_sha256 (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (int) ; 

int
main(void)
{
    unsigned char *secondkey;
    unsigned char *c;
    unsigned char *noncesuffix;
    unsigned char *in;
    unsigned char *output;
    unsigned char *h;
    size_t         output_len = 64 * 256 * 256;
    size_t         pos = 0;
    int            i;

    pos = 0;
    secondkey = (unsigned char *) sodium_malloc(32);
    memcpy(secondkey, SECONDKEY, 32);
    noncesuffix = (unsigned char *) sodium_malloc(8);
    memcpy(noncesuffix, NONCESUFFIX, 8);
    c = (unsigned char *) sodium_malloc(16);
    memcpy(c, C, 16);
    in = (unsigned char *) sodium_malloc(16);
    output = (unsigned char *) sodium_malloc(output_len);
    h = (unsigned char *) sodium_malloc(32);

    for (i = 0; i < 8; i++) {
        in[i] = noncesuffix[i];
    }
    for (; i < 16; i++) {
        in[i] = 0;
    }
    do {
        do {
            crypto_core_salsa20(output + pos, in, secondkey, c);
            pos += 64;
            in[8]++;
        } while (in[8] != 0);
        in[9]++;
    } while (in[9] != 0);

    crypto_hash_sha256(h, output, output_len);

    for (i = 0; i < 32; ++i) {
        printf("%02x", h[i]);
    }
    printf("\n");

#ifndef SODIUM_LIBRARY_MINIMAL
    pos = 0;
    do {
        do {
            crypto_core_salsa2012(output + pos, in, secondkey, c);
            pos += 64;
            in[8]++;
        } while (in[8] != 0);
        in[9]++;
    } while (in[9] != 0);

    crypto_hash_sha256(h, output, output_len);

    for (i = 0; i < 32; ++i) {
        printf("%02x", h[i]);
    }
    printf("\n");

    pos = 0;
    do {
        do {
            crypto_core_salsa208(output + pos, in, secondkey, c);
            pos += 64;
            in[8]++;
        } while (in[8] != 0);
        in[9]++;
    } while (in[9] != 0);

    crypto_hash_sha256(h, output, output_len);

    for (i = 0; i < 32; ++i) {
        printf("%02x", h[i]);
    }
    printf("\n");
#else
    printf("a4e3147dddd2ba7775939b50208a22eb3277d4e4bad8a1cfbc999c6bd392b638\n"
           "017421baa9959cbe894bd003ec87938254f47c1e757eb66cf89c353d0c2b68de\n");
#endif

    sodium_free(h);
    sodium_free(output);
    sodium_free(in);
    sodium_free(c);
    sodium_free(noncesuffix);
    sodium_free(secondkey);

    assert(crypto_core_salsa20_outputbytes() == crypto_core_salsa20_OUTPUTBYTES);
    assert(crypto_core_salsa20_inputbytes() == crypto_core_salsa20_INPUTBYTES);
    assert(crypto_core_salsa20_keybytes() == crypto_core_salsa20_KEYBYTES);
    assert(crypto_core_salsa20_constbytes() == crypto_core_salsa20_CONSTBYTES);

    return 0;
}