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
struct TYPE_3__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; scalar_t__ infinity; } ;
typedef  TYPE_1__ secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int secp256k1_fe_is_quad_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int secp256k1_gej_has_quad_y_var(const secp256k1_gej *a) {
    secp256k1_fe yz;

    if (a->infinity) {
        return 0;
    }

    /* We rely on the fact that the Jacobi symbol of 1 / a->z^3 is the same as
     * that of a->z. Thus a->y / a->z^3 is a quadratic residue iff a->y * a->z
       is */
    secp256k1_fe_mul(&yz, &a->y, &a->z);
    return secp256k1_fe_is_quad_var(&yz);
}