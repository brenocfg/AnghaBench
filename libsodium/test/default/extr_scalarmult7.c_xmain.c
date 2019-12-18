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
 int crypto_scalarmult_curve25519 (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out1 ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  p1 ; 
 int /*<<< orphan*/  p2 ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 unsigned int* scalar ; 

int
main(void)
{
    int ret;

    scalar[0] = 1U;
    ret       = crypto_scalarmult_curve25519(out1, scalar, p1);
    assert(ret == 0);
    ret = crypto_scalarmult_curve25519(out2, scalar, p2);
    assert(ret == 0);
    printf("%d\n", !!memcmp(out1, out2, 32));

    return 0;
}