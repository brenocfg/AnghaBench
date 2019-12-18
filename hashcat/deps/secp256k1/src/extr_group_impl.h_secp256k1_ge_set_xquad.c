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
struct TYPE_3__ {int /*<<< orphan*/  y; scalar_t__ infinity; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  CURVE_B ; 
 int /*<<< orphan*/  secp256k1_fe_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_fe_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int secp256k1_fe_sqrt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int secp256k1_ge_set_xquad(secp256k1_ge *r, const secp256k1_fe *x) {
    secp256k1_fe x2, x3, c;
    r->x = *x;
    secp256k1_fe_sqr(&x2, x);
    secp256k1_fe_mul(&x3, x, &x2);
    r->infinity = 0;
    secp256k1_fe_set_int(&c, CURVE_B);
    secp256k1_fe_add(&c, &x3);
    return secp256k1_fe_sqrt(&r->y, &c);
}