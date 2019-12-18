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
 int /*<<< orphan*/  c ; 
 int /*<<< orphan*/  crypto_core_hsalsa20 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/  k ; 
 scalar_t__* out ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
main(void)
{
    int i;

    crypto_core_hsalsa20(out, in, k, c);
    for (i = 0; i < 32; ++i) {
        printf(",0x%02x", (unsigned int) out[i]);
        if (i % 8 == 7) {
            printf("\n");
        }
    }
    return 0;
}