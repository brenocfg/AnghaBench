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
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 unsigned char const SECP256K1_TAG_PUBKEY_EVEN ; 
 unsigned char const SECP256K1_TAG_PUBKEY_HYBRID_EVEN ; 
 unsigned char const SECP256K1_TAG_PUBKEY_HYBRID_ODD ; 
 unsigned char const SECP256K1_TAG_PUBKEY_ODD ; 
 unsigned char const SECP256K1_TAG_PUBKEY_UNCOMPRESSED ; 
 int secp256k1_fe_is_odd (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_fe_set_b32 (int /*<<< orphan*/ *,unsigned char const*) ; 
 int secp256k1_ge_is_valid_var (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_ge_set_xo_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_ge_set_xy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int secp256k1_eckey_pubkey_parse(secp256k1_ge *elem, const unsigned char *pub, size_t size) {
    if (size == 33 && (pub[0] == SECP256K1_TAG_PUBKEY_EVEN || pub[0] == SECP256K1_TAG_PUBKEY_ODD)) {
        secp256k1_fe x;
        return secp256k1_fe_set_b32(&x, pub+1) && secp256k1_ge_set_xo_var(elem, &x, pub[0] == SECP256K1_TAG_PUBKEY_ODD);
    } else if (size == 65 && (pub[0] == SECP256K1_TAG_PUBKEY_UNCOMPRESSED || pub[0] == SECP256K1_TAG_PUBKEY_HYBRID_EVEN || pub[0] == SECP256K1_TAG_PUBKEY_HYBRID_ODD)) {
        secp256k1_fe x, y;
        if (!secp256k1_fe_set_b32(&x, pub+1) || !secp256k1_fe_set_b32(&y, pub+33)) {
            return 0;
        }
        secp256k1_ge_set_xy(elem, &x, &y);
        if ((pub[0] == SECP256K1_TAG_PUBKEY_HYBRID_EVEN || pub[0] == SECP256K1_TAG_PUBKEY_HYBRID_ODD) &&
            secp256k1_fe_is_odd(&y) != (pub[0] == SECP256K1_TAG_PUBKEY_HYBRID_ODD)) {
            return 0;
        }
        return secp256k1_ge_is_valid_var(elem);
    } else {
        return 0;
    }
}