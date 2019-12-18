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
struct TYPE_6__ {scalar_t__ usage; scalar_t__ selector; scalar_t__ mtype; int /*<<< orphan*/  spki; } ;
typedef  TYPE_1__ danetls_record ;
struct TYPE_7__ {int num_untrusted; int bare_ta_signed; int /*<<< orphan*/  chain; TYPE_3__* dane; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_8__ {int mdpth; TYPE_1__* mtlsa; int /*<<< orphan*/ * mcert; int /*<<< orphan*/  trecs; } ;
typedef  TYPE_3__ SSL_DANE ;

/* Variables and functions */
 scalar_t__ DANETLS_MATCHING_FULL ; 
 scalar_t__ DANETLS_SELECTOR_SPKI ; 
 scalar_t__ DANETLS_USAGE_DANE_TA ; 
 int X509_TRUST_TRUSTED ; 
 int X509_TRUST_UNTRUSTED ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_X509_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_X509_value (int /*<<< orphan*/ ,int) ; 
 int sk_danetls_record_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_danetls_record_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_dane_pkeys(X509_STORE_CTX *ctx)
{
    SSL_DANE *dane = ctx->dane;
    danetls_record *t;
    int num = ctx->num_untrusted;
    X509 *cert = sk_X509_value(ctx->chain, num - 1);
    int recnum = sk_danetls_record_num(dane->trecs);
    int i;

    for (i = 0; i < recnum; ++i) {
        t = sk_danetls_record_value(dane->trecs, i);
        if (t->usage != DANETLS_USAGE_DANE_TA ||
            t->selector != DANETLS_SELECTOR_SPKI ||
            t->mtype != DANETLS_MATCHING_FULL ||
            X509_verify(cert, t->spki) <= 0)
            continue;

        /* Clear any PKIX-?? matches that failed to extend to a full chain */
        X509_free(dane->mcert);
        dane->mcert = NULL;

        /* Record match via a bare TA public key */
        ctx->bare_ta_signed = 1;
        dane->mdpth = num - 1;
        dane->mtlsa = t;

        /* Prune any excess chain certificates */
        num = sk_X509_num(ctx->chain);
        for (; num > ctx->num_untrusted; --num)
            X509_free(sk_X509_pop(ctx->chain));

        return X509_TRUST_TRUSTED;
    }

    return X509_TRUST_UNTRUSTED;
}