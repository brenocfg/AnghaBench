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
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int ECMULT_TABLE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINDOW_A ; 
 int /*<<< orphan*/  secp256k1_ecmult_odd_multiples_table (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_ge_globalz_set_table_gej (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void secp256k1_ecmult_odd_multiples_table_globalz_windowa(secp256k1_ge *pre, secp256k1_fe *globalz, const secp256k1_gej *a) {
    secp256k1_gej prej[ECMULT_TABLE_SIZE(WINDOW_A)];
    secp256k1_fe zr[ECMULT_TABLE_SIZE(WINDOW_A)];

    /* Compute the odd multiples in Jacobian form. */
    secp256k1_ecmult_odd_multiples_table(ECMULT_TABLE_SIZE(WINDOW_A), prej, zr, a);
    /* Bring them to the same Z denominator. */
    secp256k1_ge_globalz_set_table_gej(ECMULT_TABLE_SIZE(WINDOW_A), pre, globalz, prej, zr);
}