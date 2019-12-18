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
typedef  int /*<<< orphan*/  crypto_onetimeauth_state ;

/* Variables and functions */
 scalar_t__* a ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ c ; 
 int /*<<< orphan*/  crypto_onetimeauth (scalar_t__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 unsigned int crypto_onetimeauth_bytes () ; 
 int /*<<< orphan*/  crypto_onetimeauth_final (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int crypto_onetimeauth_keybytes () ; 
 unsigned int crypto_onetimeauth_poly1305_bytes () ; 
 unsigned int crypto_onetimeauth_poly1305_keybytes () ; 
 int crypto_onetimeauth_poly1305_statebytes () ; 
 int /*<<< orphan*/  crypto_onetimeauth_primitive () ; 
 int crypto_onetimeauth_statebytes () ; 
 int /*<<< orphan*/  crypto_onetimeauth_update (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
main(void)
{
    crypto_onetimeauth_state st;
    int                      i;

    assert(crypto_onetimeauth_statebytes() == sizeof st);
    crypto_onetimeauth(a, c, 131, rs);
    for (i = 0; i < 16; ++i) {
        printf(",0x%02x", (unsigned int) a[i]);
        if (i % 8 == 7)
            printf("\n");
    }

    memset(a, 0, sizeof a);
    crypto_onetimeauth_init(&st, rs);
    crypto_onetimeauth_update(&st, c, 100);
    crypto_onetimeauth_update(&st, c, 0);
    crypto_onetimeauth_update(&st, c + 100, 31);
    crypto_onetimeauth_final(&st, a);
    for (i = 0; i < 16; ++i) {
        printf(",0x%02x", (unsigned int) a[i]);
        if (i % 8 == 7)
            printf("\n");
    }

    assert(crypto_onetimeauth_bytes() > 0U);
    assert(crypto_onetimeauth_keybytes() > 0U);
    assert(strcmp(crypto_onetimeauth_primitive(), "poly1305") == 0);
    assert(crypto_onetimeauth_poly1305_bytes() == crypto_onetimeauth_bytes());
    assert(crypto_onetimeauth_poly1305_keybytes() ==
           crypto_onetimeauth_keybytes());
    assert(crypto_onetimeauth_statebytes() > 0);
    assert(crypto_onetimeauth_statebytes() == crypto_onetimeauth_poly1305_statebytes());

    return 0;
}