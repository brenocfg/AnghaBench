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
 int /*<<< orphan*/  random_fe_non_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ secp256k1_fe_sqrt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void random_fe_non_square(secp256k1_fe *ns) {
    secp256k1_fe r;
    random_fe_non_zero(ns);
    if (secp256k1_fe_sqrt(&r, ns)) {
        secp256k1_fe_negate(ns, ns, 1);
    }
}