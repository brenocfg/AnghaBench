#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_30__ {int sig_idx; scalar_t__ sig; int curve; scalar_t__ const sigalg; } ;
struct TYPE_29__ {size_t shared_sigalgslen; TYPE_5__* s3; TYPE_2__* cert; scalar_t__ server; TYPE_7__** shared_sigalgs; } ;
struct TYPE_27__ {TYPE_7__ const* sigalg; TYPE_3__* cert; int /*<<< orphan*/ * peer_sigalgs; TYPE_1__* new_cipher; } ;
struct TYPE_28__ {TYPE_4__ tmp; } ;
struct TYPE_26__ {int /*<<< orphan*/ * privatekey; } ;
struct TYPE_25__ {TYPE_3__* key; TYPE_3__* pkeys; } ;
struct TYPE_24__ {int algorithm_auth; } ;
typedef  TYPE_6__ SSL ;
typedef  TYPE_7__ SIGALG_LOOKUP ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int EC_GROUP_get_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_PKEY_RSA_PSS ; 
 int /*<<< orphan*/  EVP_PKEY_get0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CHOOSE_SIGALG ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_6__*) ; 
 size_t SSL_PKEY_ECC ; 
 int /*<<< orphan*/  SSL_R_NO_SUITABLE_SIGNATURE_ALGORITHM ; 
 int /*<<< orphan*/  SSL_R_WRONG_SIGNATURE_TYPE ; 
 scalar_t__ SSL_USE_SIGALGS (TYPE_6__*) ; 
 int SSL_aCERT ; 
 int /*<<< orphan*/  SSLfatal (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* find_sig_alg (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ has_usable_cert (TYPE_6__*,TYPE_7__ const*,int) ; 
 int /*<<< orphan*/  rsa_pss_check_min_key_size (int /*<<< orphan*/ ,TYPE_7__ const*) ; 
 int /*<<< orphan*/  ssl_has_cert (TYPE_6__*,int) ; 
 int tls12_get_cert_sigalg_idx (TYPE_6__*,TYPE_7__ const*) ; 
 size_t tls12_get_psigalgs (TYPE_6__*,int,scalar_t__ const**) ; 
 TYPE_7__* tls1_get_legacy_sigalg (TYPE_6__*,int) ; 
 scalar_t__ tls1_suiteb (TYPE_6__*) ; 

int tls_choose_sigalg(SSL *s, int fatalerrs)
{
    const SIGALG_LOOKUP *lu = NULL;
    int sig_idx = -1;

    s->s3->tmp.cert = NULL;
    s->s3->tmp.sigalg = NULL;

    if (SSL_IS_TLS13(s)) {
        lu = find_sig_alg(s, NULL, NULL);
        if (lu == NULL) {
            if (!fatalerrs)
                return 1;
            SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS_CHOOSE_SIGALG,
                     SSL_R_NO_SUITABLE_SIGNATURE_ALGORITHM);
            return 0;
        }
    } else {
        /* If ciphersuite doesn't require a cert nothing to do */
        if (!(s->s3->tmp.new_cipher->algorithm_auth & SSL_aCERT))
            return 1;
        if (!s->server && !ssl_has_cert(s, s->cert->key - s->cert->pkeys))
                return 1;

        if (SSL_USE_SIGALGS(s)) {
            size_t i;
            if (s->s3->tmp.peer_sigalgs != NULL) {
#ifndef OPENSSL_NO_EC
                int curve;

                /* For Suite B need to match signature algorithm to curve */
                if (tls1_suiteb(s)) {
                    EC_KEY *ec = EVP_PKEY_get0_EC_KEY(s->cert->pkeys[SSL_PKEY_ECC].privatekey);
                    curve = EC_GROUP_get_curve_name(EC_KEY_get0_group(ec));
                } else {
                    curve = -1;
                }
#endif

                /*
                 * Find highest preference signature algorithm matching
                 * cert type
                 */
                for (i = 0; i < s->shared_sigalgslen; i++) {
                    lu = s->shared_sigalgs[i];

                    if (s->server) {
                        if ((sig_idx = tls12_get_cert_sigalg_idx(s, lu)) == -1)
                            continue;
                    } else {
                        int cc_idx = s->cert->key - s->cert->pkeys;

                        sig_idx = lu->sig_idx;
                        if (cc_idx != sig_idx)
                            continue;
                    }
                    /* Check that we have a cert, and sig_algs_cert */
                    if (!has_usable_cert(s, lu, sig_idx))
                        continue;
                    if (lu->sig == EVP_PKEY_RSA_PSS) {
                        /* validate that key is large enough for the signature algorithm */
                        EVP_PKEY *pkey = s->cert->pkeys[sig_idx].privatekey;

                        if (!rsa_pss_check_min_key_size(EVP_PKEY_get0(pkey), lu))
                            continue;
                    }
#ifndef OPENSSL_NO_EC
                    if (curve == -1 || lu->curve == curve)
#endif
                        break;
                }
                if (i == s->shared_sigalgslen) {
                    if (!fatalerrs)
                        return 1;
                    SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                             SSL_F_TLS_CHOOSE_SIGALG,
                             SSL_R_NO_SUITABLE_SIGNATURE_ALGORITHM);
                    return 0;
                }
            } else {
                /*
                 * If we have no sigalg use defaults
                 */
                const uint16_t *sent_sigs;
                size_t sent_sigslen;

                if ((lu = tls1_get_legacy_sigalg(s, -1)) == NULL) {
                    if (!fatalerrs)
                        return 1;
                    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CHOOSE_SIGALG,
                             ERR_R_INTERNAL_ERROR);
                    return 0;
                }

                /* Check signature matches a type we sent */
                sent_sigslen = tls12_get_psigalgs(s, 1, &sent_sigs);
                for (i = 0; i < sent_sigslen; i++, sent_sigs++) {
                    if (lu->sigalg == *sent_sigs
                            && has_usable_cert(s, lu, lu->sig_idx))
                        break;
                }
                if (i == sent_sigslen) {
                    if (!fatalerrs)
                        return 1;
                    SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                             SSL_F_TLS_CHOOSE_SIGALG,
                             SSL_R_WRONG_SIGNATURE_TYPE);
                    return 0;
                }
            }
        } else {
            if ((lu = tls1_get_legacy_sigalg(s, -1)) == NULL) {
                if (!fatalerrs)
                    return 1;
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CHOOSE_SIGALG,
                         ERR_R_INTERNAL_ERROR);
                return 0;
            }
        }
    }
    if (sig_idx == -1)
        sig_idx = lu->sig_idx;
    s->s3->tmp.cert = &s->cert->pkeys[sig_idx];
    s->cert->key = s->s3->tmp.cert;
    s->s3->tmp.sigalg = lu;
    return 1;
}