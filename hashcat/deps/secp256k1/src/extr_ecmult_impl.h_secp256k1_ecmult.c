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
struct secp256k1_strauss_state {struct secp256k1_strauss_point_state* ps; int /*<<< orphan*/ * pre_a_lam; int /*<<< orphan*/ * pre_a; int /*<<< orphan*/ * zr; int /*<<< orphan*/ * prej; } ;
struct secp256k1_strauss_point_state {int dummy; } ;
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_context ;

/* Variables and functions */
 int ECMULT_TABLE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINDOW_A ; 
 int /*<<< orphan*/  secp256k1_ecmult_strauss_wnaf (int /*<<< orphan*/  const*,struct secp256k1_strauss_state*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void secp256k1_ecmult(const secp256k1_ecmult_context *ctx, secp256k1_gej *r, const secp256k1_gej *a, const secp256k1_scalar *na, const secp256k1_scalar *ng) {
    secp256k1_gej prej[ECMULT_TABLE_SIZE(WINDOW_A)];
    secp256k1_fe zr[ECMULT_TABLE_SIZE(WINDOW_A)];
    secp256k1_ge pre_a[ECMULT_TABLE_SIZE(WINDOW_A)];
    struct secp256k1_strauss_point_state ps[1];
#ifdef USE_ENDOMORPHISM
    secp256k1_ge pre_a_lam[ECMULT_TABLE_SIZE(WINDOW_A)];
#endif
    struct secp256k1_strauss_state state;

    state.prej = prej;
    state.zr = zr;
    state.pre_a = pre_a;
#ifdef USE_ENDOMORPHISM
    state.pre_a_lam = pre_a_lam;
#endif
    state.ps = ps;
    secp256k1_ecmult_strauss_wnaf(ctx, &state, r, 1, a, na, ng);
}