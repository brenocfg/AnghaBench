#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ num_untrusted; int /*<<< orphan*/  chain; TYPE_1__* param; TYPE_3__* dane; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_12__ {int pdpth; scalar_t__ mdpth; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  trust; } ;
typedef  TYPE_3__ SSL_DANE ;

/* Variables and functions */
 int /*<<< orphan*/  DANETLS_ENABLED (TYPE_3__*) ; 
 scalar_t__ DANETLS_HAS_TA (TYPE_3__*) ; 
#define  X509_TRUST_REJECTED 129 
#define  X509_TRUST_TRUSTED 128 
 int X509_TRUST_UNTRUSTED ; 
 int /*<<< orphan*/  X509_V_ERR_CERT_REJECTED ; 
 int X509_V_FLAG_PARTIAL_CHAIN ; 
 int X509_check_trust (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int check_dane_issuer (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * lookup_cert_match (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify_cb_cert (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_trust(X509_STORE_CTX *ctx, int num_untrusted)
{
    int i;
    X509 *x = NULL;
    X509 *mx;
    SSL_DANE *dane = ctx->dane;
    int num = sk_X509_num(ctx->chain);
    int trust;

    /*
     * Check for a DANE issuer at depth 1 or greater, if it is a DANE-TA(2)
     * match, we're done, otherwise we'll merely record the match depth.
     */
    if (DANETLS_HAS_TA(dane) && num_untrusted > 0 && num_untrusted < num) {
        switch (trust = check_dane_issuer(ctx, num_untrusted)) {
        case X509_TRUST_TRUSTED:
        case X509_TRUST_REJECTED:
            return trust;
        }
    }

    /*
     * Check trusted certificates in chain at depth num_untrusted and up.
     * Note, that depths 0..num_untrusted-1 may also contain trusted
     * certificates, but the caller is expected to have already checked those,
     * and wants to incrementally check just any added since.
     */
    for (i = num_untrusted; i < num; i++) {
        x = sk_X509_value(ctx->chain, i);
        trust = X509_check_trust(x, ctx->param->trust, 0);
        /* If explicitly trusted return trusted */
        if (trust == X509_TRUST_TRUSTED)
            goto trusted;
        if (trust == X509_TRUST_REJECTED)
            goto rejected;
    }

    /*
     * If we are looking at a trusted certificate, and accept partial chains,
     * the chain is PKIX trusted.
     */
    if (num_untrusted < num) {
        if (ctx->param->flags & X509_V_FLAG_PARTIAL_CHAIN)
            goto trusted;
        return X509_TRUST_UNTRUSTED;
    }

    if (num_untrusted == num && ctx->param->flags & X509_V_FLAG_PARTIAL_CHAIN) {
        /*
         * Last-resort call with no new trusted certificates, check the leaf
         * for a direct trust store match.
         */
        i = 0;
        x = sk_X509_value(ctx->chain, i);
        mx = lookup_cert_match(ctx, x);
        if (!mx)
            return X509_TRUST_UNTRUSTED;

        /*
         * Check explicit auxiliary trust/reject settings.  If none are set,
         * we'll accept X509_TRUST_UNTRUSTED when not self-signed.
         */
        trust = X509_check_trust(mx, ctx->param->trust, 0);
        if (trust == X509_TRUST_REJECTED) {
            X509_free(mx);
            goto rejected;
        }

        /* Replace leaf with trusted match */
        (void) sk_X509_set(ctx->chain, 0, mx);
        X509_free(x);
        ctx->num_untrusted = 0;
        goto trusted;
    }

    /*
     * If no trusted certs in chain at all return untrusted and allow
     * standard (no issuer cert) etc errors to be indicated.
     */
    return X509_TRUST_UNTRUSTED;

 rejected:
    if (!verify_cb_cert(ctx, x, i, X509_V_ERR_CERT_REJECTED))
        return X509_TRUST_REJECTED;
    return X509_TRUST_UNTRUSTED;

 trusted:
    if (!DANETLS_ENABLED(dane))
        return X509_TRUST_TRUSTED;
    if (dane->pdpth < 0)
        dane->pdpth = num_untrusted;
    /* With DANE, PKIX alone is not trusted until we have both */
    if (dane->mdpth >= 0)
        return X509_TRUST_TRUSTED;
    return X509_TRUST_UNTRUSTED;
}