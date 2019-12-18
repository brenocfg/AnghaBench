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
 int secp256k1_fe_equal_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize_weak (int /*<<< orphan*/ *) ; 

int check_fe_equal(const secp256k1_fe *a, const secp256k1_fe *b) {
    secp256k1_fe an = *a;
    secp256k1_fe bn = *b;
    secp256k1_fe_normalize_weak(&an);
    secp256k1_fe_normalize_var(&bn);
    return secp256k1_fe_equal_var(&an, &bn);
}