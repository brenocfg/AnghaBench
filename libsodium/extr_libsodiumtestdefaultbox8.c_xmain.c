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
 int /*<<< orphan*/  alicepk ; 
 int /*<<< orphan*/  alicesk ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bobpk ; 
 int /*<<< orphan*/  bobsk ; 
 int crypto_box (unsigned char*,unsigned char*,size_t,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t crypto_box_NONCEBYTES ; 
 size_t crypto_box_ZEROBYTES ; 
 int /*<<< orphan*/  crypto_box_keypair (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_box_open (unsigned char*,unsigned char*,size_t,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* n ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t rand () ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,size_t) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (size_t) ; 

int
main(void)
{
    unsigned char *m;
    unsigned char *c;
    unsigned char *m2;
    size_t         mlen;
    size_t         mlen_max = 1000;
    size_t         i;
    int            faults;
    int            ret;

    m  = (unsigned char *) sodium_malloc(mlen_max);
    c  = (unsigned char *) sodium_malloc(mlen_max);
    m2 = (unsigned char *) sodium_malloc(mlen_max);
    crypto_box_keypair(alicepk, alicesk);
    crypto_box_keypair(bobpk, bobsk);
    for (mlen = 0; mlen + crypto_box_ZEROBYTES <= mlen_max; mlen++) {
        randombytes_buf(n, crypto_box_NONCEBYTES);
        randombytes_buf(m + crypto_box_ZEROBYTES, mlen);
        ret = crypto_box(c, m, mlen + crypto_box_ZEROBYTES, n, bobpk, alicesk);
        assert(ret == 0);
#ifdef BROWSER_TESTS
        faults = 1;
#else
        faults = 5;
#endif
        while (faults > 0) {
            c[rand() % (mlen + crypto_box_ZEROBYTES)] = rand();
            if (crypto_box_open(m2, c, mlen + crypto_box_ZEROBYTES, n, alicepk,
                                bobsk) == 0) {
                for (i = 0; i < mlen + crypto_box_ZEROBYTES; ++i) {
                    if (m2[i] != m[i]) {
                        printf("forgery\n");
                        return 100;
                    }
                }
            } else {
                faults--;
            }
        }
    }
    sodium_free(m);
    sodium_free(c);
    sodium_free(m2);

    return 0;
}