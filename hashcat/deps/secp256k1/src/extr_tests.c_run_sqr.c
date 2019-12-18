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
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_fe_mul_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_fe_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_fe_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void run_sqr(void) {
    secp256k1_fe x, s;

    {
        int i;
        secp256k1_fe_set_int(&x, 1);
        secp256k1_fe_negate(&x, &x, 1);

        for (i = 1; i <= 512; ++i) {
            secp256k1_fe_mul_int(&x, 2);
            secp256k1_fe_normalize(&x);
            secp256k1_fe_sqr(&s, &x);
        }
    }
}