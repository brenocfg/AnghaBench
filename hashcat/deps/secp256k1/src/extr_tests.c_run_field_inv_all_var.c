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
 int /*<<< orphan*/  secp256k1_fe_inv_all_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int secp256k1_rand_int (int) ; 

void run_field_inv_all_var(void) {
    secp256k1_fe x[16], xi[16], xii[16];
    int i;
    /* Check it's safe to call for 0 elements */
    secp256k1_fe_inv_all_var(xi, x, 0);
    for (i = 0; i < count; i++) {
        size_t j;
        size_t len = secp256k1_rand_int(15) + 1;
        for (j = 0; j < len; j++) {
            random_fe_non_zero(&x[j]);
        }
        secp256k1_fe_inv_all_var(xi, x, len);
        for (j = 0; j < len; j++) {
            CHECK(check_fe_inverse(&x[j], &xi[j]));
        }
        secp256k1_fe_inv_all_var(xii, xi, len);
        for (j = 0; j < len; j++) {
            CHECK(check_fe_equal(&x[j], &xii[j]));
        }
    }
}