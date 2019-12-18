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
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ ge_p3 ;
typedef  int /*<<< orphan*/  fe ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (int*,int) ; 
 int /*<<< orphan*/  fe_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_invert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_tobytes (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ge_scalarmult_base (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

void X25519_public_from_private(uint8_t out_public_value[32],
                                const uint8_t private_key[32])
{
    uint8_t e[32];
    ge_p3 A;
    fe zplusy, zminusy, zminusy_inv;

    memcpy(e, private_key, 32);
    e[0] &= 248;
    e[31] &= 127;
    e[31] |= 64;

    ge_scalarmult_base(&A, e);

    /*
     * We only need the u-coordinate of the curve25519 point.
     * The map is u=(y+1)/(1-y). Since y=Y/Z, this gives
     * u=(Z+Y)/(Z-Y).
     */
    fe_add(zplusy, A.Z, A.Y);
    fe_sub(zminusy, A.Z, A.Y);
    fe_invert(zminusy_inv, zminusy);
    fe_mul(zplusy, zplusy, zminusy_inv);
    fe_tobytes(out_public_value, zplusy);

    OPENSSL_cleanse(e, sizeof(e));
}