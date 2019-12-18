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
struct TYPE_3__ {int /*<<< orphan*/ * nonce; } ;
typedef  TYPE_1__ TS_TST_INFO ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 scalar_t__ ASN1_INTEGER_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TS_F_TS_CHECK_NONCES ; 
 int /*<<< orphan*/  TS_R_NONCE_MISMATCH ; 
 int /*<<< orphan*/  TS_R_NONCE_NOT_RETURNED ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts_check_nonces(const ASN1_INTEGER *a, TS_TST_INFO *tst_info)
{
    const ASN1_INTEGER *b = tst_info->nonce;

    if (!b) {
        TSerr(TS_F_TS_CHECK_NONCES, TS_R_NONCE_NOT_RETURNED);
        return 0;
    }

    /* No error if a nonce is returned without being requested. */
    if (ASN1_INTEGER_cmp(a, b) != 0) {
        TSerr(TS_F_TS_CHECK_NONCES, TS_R_NONCE_MISMATCH);
        return 0;
    }

    return 1;
}