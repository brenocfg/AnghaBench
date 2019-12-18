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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  crypto_generichash_state ;

/* Variables and functions */
 scalar_t__ MAXLEN ; 
 int MAX_ITER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crypto_generichash (unsigned char*,size_t,unsigned char*,size_t,unsigned char*,size_t) ; 
 scalar_t__ crypto_generichash_BYTES_MAX ; 
 size_t crypto_generichash_BYTES_MIN ; 
 scalar_t__ crypto_generichash_KEYBYTES_MAX ; 
 size_t crypto_generichash_KEYBYTES_MIN ; 
 int /*<<< orphan*/  crypto_generichash_final (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  crypto_generichash_init (int /*<<< orphan*/ *,unsigned char*,size_t,size_t) ; 
 int /*<<< orphan*/  crypto_generichash_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,size_t) ; 
 size_t randombytes_uniform (scalar_t__) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (size_t) ; 

__attribute__((used)) static void
mm_generichash(void)
{
    crypto_generichash_state st;
    unsigned char *h, *h2;
    unsigned char *k;
    unsigned char *m;
    size_t         hlen;
    size_t         klen;
    size_t         mlen;
    size_t         l1, l2;
    int            i;

    for (i = 0; i < MAX_ITER; i++) {
        mlen = randombytes_uniform(MAXLEN);
        m = (unsigned char *) sodium_malloc(mlen);
        klen = randombytes_uniform(crypto_generichash_KEYBYTES_MAX -
                                   crypto_generichash_KEYBYTES_MIN + 1U)
            + crypto_generichash_KEYBYTES_MIN;
        k = (unsigned char *) sodium_malloc(klen);
        hlen = randombytes_uniform(crypto_generichash_BYTES_MAX -
                                   crypto_generichash_BYTES_MIN + 1U)
            + crypto_generichash_BYTES_MIN;
        h = (unsigned char *) sodium_malloc(hlen);
        h2 = (unsigned char *) sodium_malloc(hlen);

        randombytes_buf(k, klen);
        randombytes_buf(m, mlen);

        crypto_generichash_init(&st, k, klen, hlen);
        l1 = randombytes_uniform((uint32_t) mlen);
        l2 = randombytes_uniform((uint32_t) (mlen - l1));
        crypto_generichash_update(&st, m, l1);
        crypto_generichash_update(&st, m + l1, l2);
        crypto_generichash_update(&st, m + l1 + l2, mlen - l1 - l2);
        crypto_generichash_final(&st, h, hlen);

        crypto_generichash(h2, hlen, m, mlen, k, klen);

        assert(memcmp(h, h2, hlen) == 0);

        sodium_free(h2);
        sodium_free(h);
        sodium_free(k);
        sodium_free(m);
    }
}