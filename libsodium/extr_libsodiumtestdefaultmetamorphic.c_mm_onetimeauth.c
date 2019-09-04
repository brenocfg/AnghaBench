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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  crypto_onetimeauth_state ;

/* Variables and functions */
 int /*<<< orphan*/  MAXLEN ; 
 int MAX_ITER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crypto_onetimeauth (unsigned char*,unsigned char*,size_t,unsigned char*) ; 
 size_t crypto_onetimeauth_BYTES ; 
 size_t crypto_onetimeauth_KEYBYTES ; 
 int /*<<< orphan*/  crypto_onetimeauth_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_init (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_keygen (unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,size_t) ; 
 size_t randombytes_uniform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (size_t) ; 

__attribute__((used)) static void
mm_onetimeauth(void)
{
    crypto_onetimeauth_state st;
    unsigned char *h, *h2;
    unsigned char *k;
    unsigned char *m;
    size_t         mlen;
    size_t         l1, l2;
    int            i;

    for (i = 0; i < MAX_ITER; i++) {
        mlen = randombytes_uniform(MAXLEN);
        m = (unsigned char *) sodium_malloc(mlen);
        k = (unsigned char *) sodium_malloc(crypto_onetimeauth_KEYBYTES);
        h = (unsigned char *) sodium_malloc(crypto_onetimeauth_BYTES);
        h2 = (unsigned char *) sodium_malloc(crypto_onetimeauth_BYTES);

        crypto_onetimeauth_keygen(k);
        randombytes_buf(m, mlen);

        crypto_onetimeauth_init(&st, k);
        l1 = randombytes_uniform((uint32_t) mlen);
        l2 = randombytes_uniform((uint32_t) (mlen - l1));
        crypto_onetimeauth_update(&st, m, l1);
        crypto_onetimeauth_update(&st, m + l1, l2);
        crypto_onetimeauth_update(&st, m + l1 + l2, mlen - l1 - l2);
        crypto_onetimeauth_final(&st, h);

        crypto_onetimeauth(h2, m, mlen, k);

        assert(memcmp(h, h2, crypto_onetimeauth_BYTES) == 0);

        sodium_free(h2);
        sodium_free(h);
        sodium_free(k);
        sodium_free(m);
    }
}