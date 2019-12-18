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
 scalar_t__* c ; 
 int crypto_secretbox (scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crypto_secretbox_boxzerobytes () ; 
 unsigned int crypto_secretbox_keybytes () ; 
 unsigned int crypto_secretbox_macbytes () ; 
 unsigned int crypto_secretbox_messagebytes_max () ; 
 unsigned int crypto_secretbox_noncebytes () ; 
 int /*<<< orphan*/  crypto_secretbox_primitive () ; 
 unsigned int crypto_secretbox_xsalsa20poly1305_boxzerobytes () ; 
 unsigned int crypto_secretbox_xsalsa20poly1305_keybytes () ; 
 unsigned int crypto_secretbox_xsalsa20poly1305_macbytes () ; 
 unsigned int crypto_secretbox_xsalsa20poly1305_messagebytes_max () ; 
 unsigned int crypto_secretbox_xsalsa20poly1305_noncebytes () ; 
 unsigned int crypto_secretbox_xsalsa20poly1305_zerobytes () ; 
 unsigned int crypto_secretbox_zerobytes () ; 
 int /*<<< orphan*/  firstkey ; 
 scalar_t__* m ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  nonce ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
main(void)
{
    int i;

    crypto_secretbox(c, m, 163, nonce, firstkey);
    for (i = 16; i < 163; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n");

    memcpy(c, m, 163);
    crypto_secretbox(c, c, 163, nonce, firstkey);
    for (i = 16; i < 163; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n");

    assert(crypto_secretbox(c, c, 31, nonce, firstkey) == -1);
    assert(crypto_secretbox(c, c, 12, nonce, firstkey) == -1);
    assert(crypto_secretbox(c, c, 1, nonce, firstkey) == -1);
    assert(crypto_secretbox(c, c, 0, nonce, firstkey) == -1);

    assert(crypto_secretbox_keybytes() > 0U);
    assert(crypto_secretbox_noncebytes() > 0U);
    assert(crypto_secretbox_zerobytes() > 0U);
    assert(crypto_secretbox_boxzerobytes() > 0U);
    assert(crypto_secretbox_macbytes() > 0U);
    assert(crypto_secretbox_messagebytes_max() > 0U);
    assert(strcmp(crypto_secretbox_primitive(), "xsalsa20poly1305") == 0);
    assert(crypto_secretbox_keybytes() ==
           crypto_secretbox_xsalsa20poly1305_keybytes());
    assert(crypto_secretbox_noncebytes() ==
           crypto_secretbox_xsalsa20poly1305_noncebytes());
    assert(crypto_secretbox_zerobytes() ==
           crypto_secretbox_xsalsa20poly1305_zerobytes());
    assert(crypto_secretbox_boxzerobytes() ==
           crypto_secretbox_xsalsa20poly1305_boxzerobytes());
    assert(crypto_secretbox_macbytes() ==
           crypto_secretbox_xsalsa20poly1305_macbytes());
    assert(crypto_secretbox_messagebytes_max() ==
           crypto_secretbox_xsalsa20poly1305_messagebytes_max());

    return 0;
}