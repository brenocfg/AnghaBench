#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ infinity; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ secp256k1_gej ;

/* Variables and functions */
 scalar_t__ secp256k1_fe_cmp_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (int /*<<< orphan*/ *) ; 

int gej_xyz_equals_gej(const secp256k1_gej *a, const secp256k1_gej *b) {
    secp256k1_gej a2;
    secp256k1_gej b2;
    int ret = 1;
    ret &= a->infinity == b->infinity;
    if (ret && !a->infinity) {
        a2 = *a;
        b2 = *b;
        secp256k1_fe_normalize(&a2.x);
        secp256k1_fe_normalize(&a2.y);
        secp256k1_fe_normalize(&a2.z);
        secp256k1_fe_normalize(&b2.x);
        secp256k1_fe_normalize(&b2.y);
        secp256k1_fe_normalize(&b2.z);
        ret &= secp256k1_fe_cmp_var(&a2.x, &b2.x) == 0;
        ret &= secp256k1_fe_cmp_var(&a2.y, &b2.y) == 0;
        ret &= secp256k1_fe_cmp_var(&a2.z, &b2.z) == 0;
    }
    return ret;
}