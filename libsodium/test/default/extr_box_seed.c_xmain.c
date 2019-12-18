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
 int /*<<< orphan*/  crypto_box_seed_keypair (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  seed ; 

int
main(void)
{
    int           i;
    unsigned char sk[32];
    unsigned char pk[32];

    crypto_box_seed_keypair(pk, sk, seed);
    for (i = 0; i < 32; ++i) {
        printf(",0x%02x", (unsigned int) pk[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    for (i = 0; i < 32; ++i) {
        printf(",0x%02x", (unsigned int) sk[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    return 0;
}