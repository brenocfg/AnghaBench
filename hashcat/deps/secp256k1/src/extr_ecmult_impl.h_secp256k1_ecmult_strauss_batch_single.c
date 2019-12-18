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
typedef  int /*<<< orphan*/  secp256k1_scratch ;
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_multi_callback ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_context ;
typedef  int /*<<< orphan*/  secp256k1_callback ;

/* Variables and functions */
 int secp256k1_ecmult_strauss_batch (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int secp256k1_ecmult_strauss_batch_single(const secp256k1_callback* error_callback, const secp256k1_ecmult_context *actx, secp256k1_scratch *scratch, secp256k1_gej *r, const secp256k1_scalar *inp_g_sc, secp256k1_ecmult_multi_callback cb, void *cbdata, size_t n) {
    return secp256k1_ecmult_strauss_batch(error_callback, actx, scratch, r, inp_g_sc, cb, cbdata, n, 0);
}