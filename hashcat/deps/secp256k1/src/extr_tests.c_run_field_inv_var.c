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
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fe_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_fe_inverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int count ; 
 int /*<<< orphan*/  random_fe_non_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_inv_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void run_field_inv_var(void) {
    secp256k1_fe x, xi, xii;
    int i;
    for (i = 0; i < 10*count; i++) {
        random_fe_non_zero(&x);
        secp256k1_fe_inv_var(&xi, &x);
        CHECK(check_fe_inverse(&x, &xi));
        secp256k1_fe_inv_var(&xii, &xi);
        CHECK(check_fe_equal(&x, &xii));
    }
}