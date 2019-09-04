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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c ; 
 int /*<<< orphan*/  crypto_core_hsalsa20 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crypto_core_hsalsa20_constbytes () ; 
 unsigned int crypto_core_hsalsa20_inputbytes () ; 
 unsigned int crypto_core_hsalsa20_keybytes () ; 
 unsigned int crypto_core_hsalsa20_outputbytes () ; 
 scalar_t__* firstkey ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  shared ; 
 int /*<<< orphan*/  zero ; 

int
main(void)
{
    int i;

    crypto_core_hsalsa20(firstkey, zero, shared, c);
    for (i = 0; i < 32; ++i) {
        if (i > 0) {
            printf(",");
        } else {
            printf(" ");
        }
        printf("0x%02x", (unsigned int) firstkey[i]);
        if (i % 8 == 7) {
            printf("\n");
        }
    }
    assert(crypto_core_hsalsa20_outputbytes() > 0U);
    assert(crypto_core_hsalsa20_inputbytes() > 0U);
    assert(crypto_core_hsalsa20_keybytes() > 0U);
    assert(crypto_core_hsalsa20_constbytes() > 0U);

    return 0;
}