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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bobsk ; 
 int /*<<< orphan*/  c ; 
 int crypto_box_BEFORENMBYTES ; 
 int crypto_box_beforenm (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_box_open (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_box_open_afternm (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__* m ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nonce ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  small_order_p ; 

int
main(void)
{
    unsigned char k[crypto_box_BEFORENMBYTES];
    int           i;
    int           ret;

    if (crypto_box_open(m, c, 163, nonce, alicepk, bobsk) == 0) {
        for (i = 32; i < 163; ++i) {
            printf(",0x%02x", (unsigned int) m[i]);
            if (i % 8 == 7)
                printf("\n");
        }
        printf("\n");
    }
    ret = crypto_box_open(m, c, 163, nonce, small_order_p, bobsk);
    assert(ret == -1);

    memset(m, 0, sizeof m);
    ret = crypto_box_beforenm(k, small_order_p, bobsk);
    assert(ret == -1);
    ret = crypto_box_beforenm(k, alicepk, bobsk);
    assert(ret == 0);
    if (crypto_box_open_afternm(m, c, 163, nonce, k) == 0) {
        for (i = 32; i < 163; ++i) {
            printf(",0x%02x", (unsigned int) m[i]);
            if (i % 8 == 7)
                printf("\n");
        }
        printf("\n");
    }
    return 0;
}