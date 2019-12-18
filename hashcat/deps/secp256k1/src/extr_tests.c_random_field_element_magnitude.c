#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int magnitude; } ;
typedef  TYPE_1__ secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  secp256k1_fe_add (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  secp256k1_fe_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  secp256k1_fe_mul_int (TYPE_1__*,int) ; 
 int /*<<< orphan*/  secp256k1_fe_negate (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (TYPE_1__*) ; 
 int secp256k1_rand_int (int) ; 

void random_field_element_magnitude(secp256k1_fe *fe) {
    secp256k1_fe zero;
    int n = secp256k1_rand_int(9);
    secp256k1_fe_normalize(fe);
    if (n == 0) {
        return;
    }
    secp256k1_fe_clear(&zero);
    secp256k1_fe_negate(&zero, &zero, 0);
    secp256k1_fe_mul_int(&zero, n - 1);
    secp256k1_fe_add(fe, &zero);
#ifdef VERIFY
    CHECK(fe->magnitude == n);
#endif
}