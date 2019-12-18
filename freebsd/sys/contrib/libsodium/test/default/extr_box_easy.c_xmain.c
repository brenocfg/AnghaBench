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
 int crypto_box_MACBYTES ; 
 int crypto_box_easy (scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_box_open_easy (scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* m ; 
 int /*<<< orphan*/  nonce ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t randombytes_uniform (int) ; 

int
main(void)
{
    size_t i;
    int    ret;

    ret = crypto_box_easy(c, m, 131, nonce, bobpk, alicesk);
    assert(ret == 0);
    for (i = 0; i < 131 + crypto_box_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");

    /* Null message */

    ret = crypto_box_easy(c, c, 0, nonce, bobpk, alicesk);
    assert(ret == 0);
    for (i = 0; i < 1 + crypto_box_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");
    ret =
        crypto_box_open_easy(c, c, crypto_box_MACBYTES, nonce, bobpk, alicesk);
    assert(ret == 0);
    for (i = 0; i < 1 + crypto_box_MACBYTES; ++i) {
        printf(",0x%02x", (unsigned int) c[i]);
    }
    printf("\n");
    c[randombytes_uniform(crypto_box_MACBYTES)]++;
    ret = crypto_box_open_easy(c, c, crypto_box_MACBYTES, nonce, bobpk, alicesk);
    assert(ret == -1);

    return 0;
}