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
 int /*<<< orphan*/  crypto_stream (scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firstkey ; 
 int /*<<< orphan*/  nonce ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__* rs ; 

int
main(void)
{
    int i;

    crypto_stream(rs, 32, nonce, firstkey);

    for (i = 0; i < 32; ++i) {
        printf(",0x%02x", (unsigned int) rs[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    return 0;
}