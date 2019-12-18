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
typedef  int /*<<< orphan*/  felem_bytearray ;
typedef  int /*<<< orphan*/  felem ;
typedef  int /*<<< orphan*/  b_out ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_bn2lebinpad (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_F_BN_TO_FELEM ; 
 int /*<<< orphan*/  EC_R_BIGNUM_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin32_to_felem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int BN_to_felem(felem out, const BIGNUM *bn)
{
    felem_bytearray b_out;
    int num_bytes;

    if (BN_is_negative(bn)) {
        ECerr(EC_F_BN_TO_FELEM, EC_R_BIGNUM_OUT_OF_RANGE);
        return 0;
    }
    num_bytes = BN_bn2lebinpad(bn, b_out, sizeof(b_out));
    if (num_bytes < 0) {
        ECerr(EC_F_BN_TO_FELEM, EC_R_BIGNUM_OUT_OF_RANGE);
        return 0;
    }
    bin32_to_felem(out, b_out);
    return 1;
}