#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  infinity; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ secp256k1_gej ;
struct TYPE_6__ {int /*<<< orphan*/  infinity; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  random_field_element_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void random_group_element_jacobian_test(secp256k1_gej *gej, const secp256k1_ge *ge) {
    secp256k1_fe z2, z3;
    do {
        random_field_element_test(&gej->z);
        if (!secp256k1_fe_is_zero(&gej->z)) {
            break;
        }
    } while(1);
    secp256k1_fe_sqr(&z2, &gej->z);
    secp256k1_fe_mul(&z3, &z2, &gej->z);
    secp256k1_fe_mul(&gej->x, &ge->x, &z2);
    secp256k1_fe_mul(&gej->y, &ge->y, &z3);
    gej->infinity = ge->infinity;
}