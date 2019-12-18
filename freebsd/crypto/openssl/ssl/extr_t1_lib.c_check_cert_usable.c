#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_11__ {int hash; int sig; } ;
struct TYPE_10__ {TYPE_2__* s3; } ;
struct TYPE_8__ {size_t peer_cert_sigalgslen; int /*<<< orphan*/ * peer_cert_sigalgs; } ;
struct TYPE_9__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ SIGALG_LOOKUP ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_pop_to_mark () ; 
 int /*<<< orphan*/  ERR_set_mark () ; 
 int EVP_PKEY_get_default_digest_nid (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  X509_get_signature_info (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* tls1_lookup_sigalg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_cert_usable(SSL *s, const SIGALG_LOOKUP *sig, X509 *x,
                             EVP_PKEY *pkey)
{
    const SIGALG_LOOKUP *lu;
    int mdnid, pknid, default_mdnid;
    size_t i;

    /* If the EVP_PKEY reports a mandatory digest, allow nothing else. */
    ERR_set_mark();
    if (EVP_PKEY_get_default_digest_nid(pkey, &default_mdnid) == 2 &&
        sig->hash != default_mdnid)
            return 0;

    /* If it didn't report a mandatory NID, for whatever reasons,
     * just clear the error and allow all hashes to be used. */
    ERR_pop_to_mark();

    if (s->s3->tmp.peer_cert_sigalgs != NULL) {
        for (i = 0; i < s->s3->tmp.peer_cert_sigalgslen; i++) {
            lu = tls1_lookup_sigalg(s->s3->tmp.peer_cert_sigalgs[i]);
            if (lu == NULL
                || !X509_get_signature_info(x, &mdnid, &pknid, NULL, NULL))
                continue;
            /*
             * TODO this does not differentiate between the
             * rsa_pss_pss_* and rsa_pss_rsae_* schemes since we do not
             * have a chain here that lets us look at the key OID in the
             * signing certificate.
             */
            if (mdnid == lu->hash && pknid == lu->sig)
                return 1;
        }
        return 0;
    }
    return 1;
}