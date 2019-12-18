#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scalar ;
struct TYPE_3__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int EXHAUSTIVE_TEST_ORDER ; 
 int /*<<< orphan*/  secp256k1_fe_get_b32 (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_b32 (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 

void r_from_k(secp256k1_scalar *r, const secp256k1_ge *group, int k) {
    secp256k1_fe x;
    unsigned char x_bin[32];
    k %= EXHAUSTIVE_TEST_ORDER;
    x = group[k].x;
    secp256k1_fe_normalize(&x);
    secp256k1_fe_get_b32(x_bin, &x);
    secp256k1_scalar_set_b32(r, x_bin, NULL);
}