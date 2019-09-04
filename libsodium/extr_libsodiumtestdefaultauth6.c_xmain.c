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
 scalar_t__* a ; 
 int /*<<< orphan*/  c ; 
 int /*<<< orphan*/  crypto_auth_hmacsha512 (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
main(void)
{
    int i;

    crypto_auth_hmacsha512(a, c, sizeof c - 1U, key);
    for (i = 0; i < 64; ++i) {
        printf(",0x%02x", (unsigned int) a[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    return 0;
}