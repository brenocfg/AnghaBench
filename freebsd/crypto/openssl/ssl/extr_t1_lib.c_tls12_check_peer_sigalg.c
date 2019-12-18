#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int const uint16_t ;
struct TYPE_20__ {scalar_t__ hash; int sig; int sig_idx; int curve; } ;
struct TYPE_19__ {TYPE_3__* s3; TYPE_1__* cert; } ;
struct TYPE_17__ {TYPE_5__ const* peer_sigalg; } ;
struct TYPE_18__ {TYPE_2__ tmp; } ;
struct TYPE_16__ {int cert_flags; } ;
typedef  TYPE_4__ SSL ;
typedef  TYPE_5__ SIGALG_LOOKUP ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int EC_GROUP_get_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int EVP_PKEY_DSA ; 
 int EVP_PKEY_EC ; 
 int EVP_PKEY_RSA ; 
 int EVP_PKEY_RSA_PSS ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 scalar_t__ NID_sha1 ; 
 scalar_t__ NID_sha224 ; 
 int NID_undef ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int SSL_CERT_FLAGS_CHECK_TLS_STRICT ; 
 int /*<<< orphan*/  SSL_F_TLS12_CHECK_PEER_SIGALG ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_R_ILLEGAL_POINT_COMPRESSION ; 
 int /*<<< orphan*/  SSL_R_UNKNOWN_DIGEST ; 
 int /*<<< orphan*/  SSL_R_WRONG_CURVE ; 
 int /*<<< orphan*/  SSL_R_WRONG_SIGNATURE_TYPE ; 
 int /*<<< orphan*/  SSL_SECOP_SIGALG_CHECK ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const TLSEXT_SIGALG_ecdsa_secp256r1_sha256 ; 
 int const TLSEXT_SIGALG_ecdsa_secp384r1_sha384 ; 
 int /*<<< orphan*/  ssl_cert_lookup_by_nid (int,size_t*) ; 
 int /*<<< orphan*/  ssl_security (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 size_t tls12_get_psigalgs (TYPE_4__*,int,int const**) ; 
 int /*<<< orphan*/  tls1_check_group_id (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tls1_check_pkey_comp (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls1_get_group_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls1_lookup_md (TYPE_5__ const*,int /*<<< orphan*/  const**) ; 
 TYPE_5__* tls1_lookup_sigalg (int const) ; 
 scalar_t__ tls1_suiteb (TYPE_4__*) ; 

int tls12_check_peer_sigalg(SSL *s, uint16_t sig, EVP_PKEY *pkey)
{
    const uint16_t *sent_sigs;
    const EVP_MD *md = NULL;
    char sigalgstr[2];
    size_t sent_sigslen, i, cidx;
    int pkeyid = EVP_PKEY_id(pkey);
    const SIGALG_LOOKUP *lu;

    /* Should never happen */
    if (pkeyid == -1)
        return -1;
    if (SSL_IS_TLS13(s)) {
        /* Disallow DSA for TLS 1.3 */
        if (pkeyid == EVP_PKEY_DSA) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS12_CHECK_PEER_SIGALG,
                     SSL_R_WRONG_SIGNATURE_TYPE);
            return 0;
        }
        /* Only allow PSS for TLS 1.3 */
        if (pkeyid == EVP_PKEY_RSA)
            pkeyid = EVP_PKEY_RSA_PSS;
    }
    lu = tls1_lookup_sigalg(sig);
    /*
     * Check sigalgs is known. Disallow SHA1/SHA224 with TLS 1.3. Check key type
     * is consistent with signature: RSA keys can be used for RSA-PSS
     */
    if (lu == NULL
        || (SSL_IS_TLS13(s) && (lu->hash == NID_sha1 || lu->hash == NID_sha224))
        || (pkeyid != lu->sig
        && (lu->sig != EVP_PKEY_RSA_PSS || pkeyid != EVP_PKEY_RSA))) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS12_CHECK_PEER_SIGALG,
                 SSL_R_WRONG_SIGNATURE_TYPE);
        return 0;
    }
    /* Check the sigalg is consistent with the key OID */
    if (!ssl_cert_lookup_by_nid(EVP_PKEY_id(pkey), &cidx)
            || lu->sig_idx != (int)cidx) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS12_CHECK_PEER_SIGALG,
                 SSL_R_WRONG_SIGNATURE_TYPE);
        return 0;
    }

#ifndef OPENSSL_NO_EC
    if (pkeyid == EVP_PKEY_EC) {

        /* Check point compression is permitted */
        if (!tls1_check_pkey_comp(s, pkey)) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                     SSL_F_TLS12_CHECK_PEER_SIGALG,
                     SSL_R_ILLEGAL_POINT_COMPRESSION);
            return 0;
        }

        /* For TLS 1.3 or Suite B check curve matches signature algorithm */
        if (SSL_IS_TLS13(s) || tls1_suiteb(s)) {
            EC_KEY *ec = EVP_PKEY_get0_EC_KEY(pkey);
            int curve = EC_GROUP_get_curve_name(EC_KEY_get0_group(ec));

            if (lu->curve != NID_undef && curve != lu->curve) {
                SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                         SSL_F_TLS12_CHECK_PEER_SIGALG, SSL_R_WRONG_CURVE);
                return 0;
            }
        }
        if (!SSL_IS_TLS13(s)) {
            /* Check curve matches extensions */
            if (!tls1_check_group_id(s, tls1_get_group_id(pkey), 1)) {
                SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                         SSL_F_TLS12_CHECK_PEER_SIGALG, SSL_R_WRONG_CURVE);
                return 0;
            }
            if (tls1_suiteb(s)) {
                /* Check sigalg matches a permissible Suite B value */
                if (sig != TLSEXT_SIGALG_ecdsa_secp256r1_sha256
                    && sig != TLSEXT_SIGALG_ecdsa_secp384r1_sha384) {
                    SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                             SSL_F_TLS12_CHECK_PEER_SIGALG,
                             SSL_R_WRONG_SIGNATURE_TYPE);
                    return 0;
                }
            }
        }
    } else if (tls1_suiteb(s)) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS12_CHECK_PEER_SIGALG,
                 SSL_R_WRONG_SIGNATURE_TYPE);
        return 0;
    }
#endif

    /* Check signature matches a type we sent */
    sent_sigslen = tls12_get_psigalgs(s, 1, &sent_sigs);
    for (i = 0; i < sent_sigslen; i++, sent_sigs++) {
        if (sig == *sent_sigs)
            break;
    }
    /* Allow fallback to SHA1 if not strict mode */
    if (i == sent_sigslen && (lu->hash != NID_sha1
        || s->cert->cert_flags & SSL_CERT_FLAGS_CHECK_TLS_STRICT)) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS12_CHECK_PEER_SIGALG,
                 SSL_R_WRONG_SIGNATURE_TYPE);
        return 0;
    }
    if (!tls1_lookup_md(lu, &md)) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS12_CHECK_PEER_SIGALG,
                 SSL_R_UNKNOWN_DIGEST);
        return 0;
    }
    if (md != NULL) {
        /*
         * Make sure security callback allows algorithm. For historical
         * reasons we have to pass the sigalg as a two byte char array.
         */
        sigalgstr[0] = (sig >> 8) & 0xff;
        sigalgstr[1] = sig & 0xff;
        if (!ssl_security(s, SSL_SECOP_SIGALG_CHECK,
                    EVP_MD_size(md) * 4, EVP_MD_type(md),
                    (void *)sigalgstr)) {
            SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS12_CHECK_PEER_SIGALG,
                     SSL_R_WRONG_SIGNATURE_TYPE);
            return 0;
        }
    }
    /* Store the sigalg the peer uses */
    s->s3->tmp.peer_sigalg = lu;
    return 1;
}