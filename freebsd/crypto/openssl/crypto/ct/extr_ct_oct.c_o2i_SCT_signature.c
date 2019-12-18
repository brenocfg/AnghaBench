#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ version; int /*<<< orphan*/  sig_alg; int /*<<< orphan*/  hash_alg; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_O2I_SCT_SIGNATURE ; 
 int /*<<< orphan*/  CT_R_SCT_INVALID_SIGNATURE ; 
 int /*<<< orphan*/  CT_R_UNSUPPORTED_VERSION ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NID_undef ; 
 scalar_t__ SCT_VERSION_V1 ; 
 scalar_t__ SCT_get_signature_nid (TYPE_1__*) ; 
 int SCT_set1_signature (TYPE_1__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  n2s (unsigned char const*,size_t) ; 

int o2i_SCT_signature(SCT *sct, const unsigned char **in, size_t len)
{
    size_t siglen;
    size_t len_remaining = len;
    const unsigned char *p;

    if (sct->version != SCT_VERSION_V1) {
        CTerr(CT_F_O2I_SCT_SIGNATURE, CT_R_UNSUPPORTED_VERSION);
        return -1;
    }
    /*
     * digitally-signed struct header: (1 byte) Hash algorithm (1 byte)
     * Signature algorithm (2 bytes + ?) Signature
     *
     * This explicitly rejects empty signatures: they're invalid for
     * all supported algorithms.
     */
    if (len <= 4) {
        CTerr(CT_F_O2I_SCT_SIGNATURE, CT_R_SCT_INVALID_SIGNATURE);
        return -1;
    }

    p = *in;
    /* Get hash and signature algorithm */
    sct->hash_alg = *p++;
    sct->sig_alg = *p++;
    if (SCT_get_signature_nid(sct) == NID_undef) {
        CTerr(CT_F_O2I_SCT_SIGNATURE, CT_R_SCT_INVALID_SIGNATURE);
        return -1;
    }
    /* Retrieve signature and check it is consistent with the buffer length */
    n2s(p, siglen);
    len_remaining -= (p - *in);
    if (siglen > len_remaining) {
        CTerr(CT_F_O2I_SCT_SIGNATURE, CT_R_SCT_INVALID_SIGNATURE);
        return -1;
    }

    if (SCT_set1_signature(sct, p, siglen) != 1)
        return -1;
    len_remaining -= siglen;
    *in = p + siglen;

    return len - len_remaining;
}