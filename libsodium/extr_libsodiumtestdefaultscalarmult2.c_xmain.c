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
 scalar_t__* bobpk ; 
 int /*<<< orphan*/  bobsk ; 
 int /*<<< orphan*/  crypto_scalarmult_base (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
main(void)
{
    int i;

    crypto_scalarmult_base(bobpk, bobsk);

    for (i = 0; i < 32; ++i) {
        if (i > 0) {
            printf(",");
        } else {
            printf(" ");
        }
        printf("0x%02x", (unsigned int) bobpk[i]);
        if (i % 8 == 7) {
            printf("\n");
        }
    }
    return 0;
}