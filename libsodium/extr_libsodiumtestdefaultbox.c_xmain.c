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
 int /*<<< orphan*/  alicesk ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bobpk ; 
 scalar_t__* c ; 
 int crypto_box (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_box_BEFORENMBYTES ; 
 int /*<<< orphan*/  crypto_box_afternm (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*) ; 
 int crypto_box_beforenm (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crypto_box_beforenmbytes () ; 
 unsigned int crypto_box_boxzerobytes () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_beforenmbytes () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_boxzerobytes () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_macbytes () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_messagebytes_max () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_noncebytes () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_publickeybytes () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_secretkeybytes () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_seedbytes () ; 
 unsigned int crypto_box_curve25519xsalsa20poly1305_zerobytes () ; 
 unsigned int crypto_box_macbytes () ; 
 unsigned int crypto_box_messagebytes_max () ; 
 unsigned int crypto_box_noncebytes () ; 
 int /*<<< orphan*/  crypto_box_primitive () ; 
 unsigned int crypto_box_publickeybytes () ; 
 unsigned int crypto_box_secretkeybytes () ; 
 unsigned int crypto_box_seedbytes () ; 
 unsigned int crypto_box_zerobytes () ; 
 int /*<<< orphan*/  m ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nonce ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  small_order_p ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
main(void)
{
    unsigned char k[crypto_box_BEFORENMBYTES];
    int           i;
    int           ret;

    ret = crypto_box(c, m, 163, nonce, bobpk, alicesk);
    assert(ret == 0);
    for (i = 16; i < 163; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n");

    ret = crypto_box(c, m, 163, nonce, small_order_p, alicesk);
    assert(ret == -1);

    memset(c, 0, sizeof c);

    ret = crypto_box_beforenm(k, bobpk, alicesk);
    assert(ret == 0);
    crypto_box_afternm(c, m, 163, nonce, k);
    for (i = 16; i < 163; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n");

    ret = crypto_box_beforenm(k, small_order_p, alicesk);
    assert(ret == -1);

    assert(crypto_box_seedbytes() > 0U);
    assert(crypto_box_publickeybytes() > 0U);
    assert(crypto_box_secretkeybytes() > 0U);
    assert(crypto_box_beforenmbytes() > 0U);
    assert(crypto_box_noncebytes() > 0U);
    assert(crypto_box_zerobytes() > 0U);
    assert(crypto_box_boxzerobytes() > 0U);
    assert(crypto_box_macbytes() > 0U);
    assert(crypto_box_messagebytes_max() > 0U);
    assert(strcmp(crypto_box_primitive(), "curve25519xsalsa20poly1305") == 0);
    assert(crypto_box_curve25519xsalsa20poly1305_seedbytes() ==
           crypto_box_seedbytes());
    assert(crypto_box_curve25519xsalsa20poly1305_publickeybytes() ==
           crypto_box_publickeybytes());
    assert(crypto_box_curve25519xsalsa20poly1305_secretkeybytes() ==
           crypto_box_secretkeybytes());
    assert(crypto_box_curve25519xsalsa20poly1305_beforenmbytes() ==
           crypto_box_beforenmbytes());
    assert(crypto_box_curve25519xsalsa20poly1305_noncebytes() ==
           crypto_box_noncebytes());
    assert(crypto_box_curve25519xsalsa20poly1305_zerobytes() ==
           crypto_box_zerobytes());
    assert(crypto_box_curve25519xsalsa20poly1305_boxzerobytes() ==
           crypto_box_boxzerobytes());
    assert(crypto_box_curve25519xsalsa20poly1305_macbytes() ==
           crypto_box_macbytes());
    assert(crypto_box_curve25519xsalsa20poly1305_messagebytes_max() ==
           crypto_box_messagebytes_max());

    return 0;
}