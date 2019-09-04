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
 int crypto_scalarmult (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* k ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
main(void)
{
    int i;
    int ret;

    ret = crypto_scalarmult(k, alicesk, bobpk);
    assert(ret == 0);

    for (i = 0; i < 32; ++i) {
        if (i > 0) {
            printf(",");
        } else {
            printf(" ");
        }
        printf("0x%02x", (unsigned int) k[i]);
        if (i % 8 == 7) {
            printf("\n");
        }
    }
    return 0;
}