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
 int crypto_secretbox_open (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firstkey ; 
 scalar_t__* m ; 
 int /*<<< orphan*/  nonce ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
main(void)
{
    int i;

    if (crypto_secretbox_open(m, c, 163, nonce, firstkey) == 0) {
        for (i = 32; i < 163; ++i) {
            printf(",0x%02x", (unsigned int) m[i]);
            if (i % 8 == 7)
                printf("\n");
        }
        printf("\n");
    }
    assert(crypto_secretbox_open(m, c, 31, nonce, firstkey) == -1);
    assert(crypto_secretbox_open(m, c, 16, nonce, firstkey) == -1);
    assert(crypto_secretbox_open(m, c, 1, nonce, firstkey) == -1);
    assert(crypto_secretbox_open(m, c, 0, nonce, firstkey) == -1);

    return 0;
}