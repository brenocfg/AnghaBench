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
typedef  int /*<<< orphan*/  crypto_auth_hmacsha512_state ;
typedef  int /*<<< orphan*/  crypto_auth_hmacsha512256_state ;
typedef  int /*<<< orphan*/  crypto_auth_hmacsha256_state ;

/* Variables and functions */
 scalar_t__* a ; 
 scalar_t__* a2 ; 
 scalar_t__* a3 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* c ; 
 int /*<<< orphan*/  crypto_auth (scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 unsigned int crypto_auth_bytes () ; 
 unsigned int crypto_auth_hmacsha256_bytes () ; 
 int /*<<< orphan*/  crypto_auth_hmacsha256_final (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  crypto_auth_hmacsha256_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int crypto_auth_hmacsha256_keybytes () ; 
 int crypto_auth_hmacsha256_statebytes () ; 
 int /*<<< orphan*/  crypto_auth_hmacsha256_update (int /*<<< orphan*/ *,scalar_t__*,unsigned int) ; 
 unsigned int crypto_auth_hmacsha512256_bytes () ; 
 int /*<<< orphan*/  crypto_auth_hmacsha512256_final (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  crypto_auth_hmacsha512256_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int crypto_auth_hmacsha512256_keybytes () ; 
 unsigned int crypto_auth_hmacsha512256_statebytes () ; 
 int /*<<< orphan*/  crypto_auth_hmacsha512256_update (int /*<<< orphan*/ *,scalar_t__*,unsigned int) ; 
 unsigned int crypto_auth_hmacsha512_bytes () ; 
 int /*<<< orphan*/  crypto_auth_hmacsha512_final (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  crypto_auth_hmacsha512_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int crypto_auth_hmacsha512_keybytes () ; 
 int crypto_auth_hmacsha512_statebytes () ; 
 int /*<<< orphan*/  crypto_auth_hmacsha512_update (int /*<<< orphan*/ *,scalar_t__*,unsigned int) ; 
 unsigned int crypto_auth_keybytes () ; 
 int /*<<< orphan*/  crypto_auth_primitive () ; 
 scalar_t__* guard_page ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  key2 ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sodium_memcmp (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
main(void)
{
    crypto_auth_hmacsha512_state st;
    crypto_auth_hmacsha256_state st256;
    crypto_auth_hmacsha512256_state st512_256;
    size_t                       i;

    assert(crypto_auth_hmacsha512_statebytes() ==
           sizeof(crypto_auth_hmacsha512_state));
    crypto_auth(a, c, sizeof c - 1U, key);
    for (i = 0; i < sizeof a; ++i) {
        printf(",0x%02x", (unsigned int) a[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n");

    crypto_auth_hmacsha512_init(&st, key, sizeof key);
    crypto_auth_hmacsha512_update(&st, c, 1U);
    crypto_auth_hmacsha512_update(&st, c, sizeof c - 2U);
    crypto_auth_hmacsha512_final(&st, a2);
    for (i = 0; i < sizeof a2; ++i) {
        printf(",0x%02x", (unsigned int) a2[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n");

    crypto_auth_hmacsha512_init(&st, key2, sizeof key2);
    crypto_auth_hmacsha512_update(&st, c, 1U);
    crypto_auth_hmacsha512_update(&st, c, sizeof c - 2U);
    crypto_auth_hmacsha512_final(&st, a2);
    for (i = 0; i < sizeof a2; ++i) {
        printf(",0x%02x", (unsigned int) a2[i]);
        if (i % 8 == 7)
            printf("\n");
    }

    memset(a2, 0, sizeof a2);
    crypto_auth_hmacsha256_init(&st256, key2, sizeof key2);
    crypto_auth_hmacsha256_update(&st256, guard_page, 0U);
    crypto_auth_hmacsha256_update(&st256, c, 1U);
    crypto_auth_hmacsha256_update(&st256, c, sizeof c - 2U);
    crypto_auth_hmacsha256_final(&st256, a2);
    for (i = 0; i < sizeof a2; ++i) {
        printf(",0x%02x", (unsigned int) a2[i]);
        if (i % 8 == 7)
            printf("\n");
    }

    /* Empty message tests: HMAC-SHA512 */
    memset(a2, 0, sizeof a2);
    crypto_auth_hmacsha512_init(&st, key, sizeof key);
    crypto_auth_hmacsha512_final(&st, a2);

    memset(a3, 0, sizeof a3);
    crypto_auth_hmacsha512_init(&st, key, sizeof key);
    crypto_auth_hmacsha512_update(&st, a2, 0U);
    crypto_auth_hmacsha512_final(&st, a3);
    assert(sodium_memcmp(a2, a3, sizeof a2) == 0);

    memset(a3, 0, sizeof a3);
    crypto_auth_hmacsha512_init(&st, key, sizeof key);
    crypto_auth_hmacsha512_update(&st, guard_page, 0U);
    crypto_auth_hmacsha512_final(&st, a3);
    assert(sodium_memcmp(a2, a3, sizeof a2) == 0);

    /* Empty message tests: HMAC-SHA512-256 */
    memset(a2, 0, sizeof a2);
    crypto_auth_hmacsha512256_init(&st512_256, key, sizeof key);
    crypto_auth_hmacsha512256_final(&st512_256, a2);

    memset(a3, 0, sizeof a3);
    crypto_auth_hmacsha512256_init(&st512_256, key, sizeof key);
    crypto_auth_hmacsha512256_update(&st512_256, a2, 0U);
    crypto_auth_hmacsha512256_final(&st512_256, a3);
    assert(sodium_memcmp(a2, a3, sizeof a2) == 0);

    memset(a3, 0, sizeof a3);
    crypto_auth_hmacsha512256_init(&st512_256, key, sizeof key);
    crypto_auth_hmacsha512256_update(&st512_256, guard_page, 0U);
    crypto_auth_hmacsha512256_final(&st512_256, a3);
    assert(sodium_memcmp(a2, a3, sizeof a2) == 0);

    /* Empty message tests: HMAC-SHA256 */

    memset(a2, 0, sizeof a2);
    crypto_auth_hmacsha256_init(&st256, key, sizeof key);
    crypto_auth_hmacsha256_final(&st256, a2);

    memset(a3, 0, sizeof a3);
    crypto_auth_hmacsha256_init(&st256, key, sizeof key);
    crypto_auth_hmacsha256_update(&st256, a2, 0U);
    crypto_auth_hmacsha256_final(&st256, a3);
    assert(sodium_memcmp(a2, a3, sizeof a2) == 0);

    memset(a3, 0, sizeof a3);
    crypto_auth_hmacsha256_init(&st256, key, sizeof key);
    crypto_auth_hmacsha256_update(&st256, guard_page, 0U);
    crypto_auth_hmacsha256_final(&st256, a3);
    assert(sodium_memcmp(a2, a3, sizeof a2) == 0);

    /* --- */

    assert(crypto_auth_bytes() > 0U);
    assert(crypto_auth_keybytes() > 0U);
    assert(strcmp(crypto_auth_primitive(), "hmacsha512256") == 0);
    assert(crypto_auth_hmacsha256_bytes() > 0U);
    assert(crypto_auth_hmacsha256_keybytes() > 0U);
    assert(crypto_auth_hmacsha512_bytes() > 0U);
    assert(crypto_auth_hmacsha512_keybytes() > 0U);
    assert(crypto_auth_hmacsha512256_bytes() == crypto_auth_bytes());
    assert(crypto_auth_hmacsha512256_keybytes() == crypto_auth_keybytes());
    assert(crypto_auth_hmacsha512256_statebytes() >=
           crypto_auth_hmacsha512256_keybytes());
    assert(crypto_auth_hmacsha256_statebytes() ==
           sizeof(crypto_auth_hmacsha256_state));
    assert(crypto_auth_hmacsha512_statebytes() ==
           sizeof(crypto_auth_hmacsha512_state));

    return 0;
}