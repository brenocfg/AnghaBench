#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ parameter; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
struct TYPE_8__ {int /*<<< orphan*/  hashed_msg; TYPE_1__* hash_algo; } ;
struct TYPE_7__ {TYPE_3__* msg_imprint; } ;
typedef  TYPE_2__ TS_TST_INFO ;
typedef  TYPE_3__ TS_MSG_IMPRINT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ASN1_STRING_length (int /*<<< orphan*/ ) ; 
 scalar_t__ ASN1_TYPE_get (scalar_t__) ; 
 scalar_t__ OBJ_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_F_TS_CHECK_IMPRINTS ; 
 int /*<<< orphan*/  TS_R_MESSAGE_IMPRINT_MISMATCH ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ V_ASN1_NULL ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ts_check_imprints(X509_ALGOR *algor_a,
                             const unsigned char *imprint_a, unsigned len_a,
                             TS_TST_INFO *tst_info)
{
    TS_MSG_IMPRINT *b = tst_info->msg_imprint;
    X509_ALGOR *algor_b = b->hash_algo;
    int ret = 0;

    if (algor_a) {
        if (OBJ_cmp(algor_a->algorithm, algor_b->algorithm))
            goto err;

        /* The parameter must be NULL in both. */
        if ((algor_a->parameter
             && ASN1_TYPE_get(algor_a->parameter) != V_ASN1_NULL)
            || (algor_b->parameter
                && ASN1_TYPE_get(algor_b->parameter) != V_ASN1_NULL))
            goto err;
    }

    ret = len_a == (unsigned)ASN1_STRING_length(b->hashed_msg) &&
        memcmp(imprint_a, ASN1_STRING_get0_data(b->hashed_msg), len_a) == 0;
 err:
    if (!ret)
        TSerr(TS_F_TS_CHECK_IMPRINTS, TS_R_MESSAGE_IMPRINT_MISMATCH);
    return ret;
}