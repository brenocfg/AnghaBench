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
typedef  int /*<<< orphan*/  secp256k1_pubkey ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secp256k1_ge_neg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_pubkey_load (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_pubkey_save (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int secp256k1_ec_pubkey_negate(const secp256k1_context* ctx, secp256k1_pubkey *pubkey) {
    int ret = 0;
    secp256k1_ge p;
    VERIFY_CHECK(ctx != NULL);
    ARG_CHECK(pubkey != NULL);

    ret = secp256k1_pubkey_load(ctx, &p, pubkey);
    memset(pubkey, 0, sizeof(*pubkey));
    if (ret) {
        secp256k1_ge_neg(&p, &p);
        secp256k1_pubkey_save(pubkey, &p);
    }
    return ret;
}