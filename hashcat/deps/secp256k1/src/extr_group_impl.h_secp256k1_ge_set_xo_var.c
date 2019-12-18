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
struct TYPE_4__ {int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int secp256k1_fe_is_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_set_xquad (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int secp256k1_ge_set_xo_var(secp256k1_ge *r, const secp256k1_fe *x, int odd) {
    if (!secp256k1_ge_set_xquad(r, x)) {
        return 0;
    }
    secp256k1_fe_normalize_var(&r->y);
    if (secp256k1_fe_is_odd(&r->y) != odd) {
        secp256k1_fe_negate(&r->y, &r->y, 1);
    }
    return 1;

}