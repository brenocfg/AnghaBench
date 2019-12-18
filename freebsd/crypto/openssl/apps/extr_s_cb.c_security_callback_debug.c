#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* old_cb ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int,void*,void*) ;int verbose; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ security_debug_ex ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char const*) ; 
 char* DH_bits (int /*<<< orphan*/ *) ; 
 char* EC_curve_nid2nist (int) ; 
 int /*<<< orphan*/  EVP_PKEY_asn1_get0_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_get0_asn1 (int /*<<< orphan*/ *) ; 
 char const* OBJ_nid2sn (int) ; 
 char const* SSL_CIPHER_get_name (void*) ; 
#define  SSL_SECOP_CA_MD 141 
#define  SSL_SECOP_COMPRESSION 140 
#define  SSL_SECOP_OTHER_CERT 139 
#define  SSL_SECOP_OTHER_CIPHER 138 
#define  SSL_SECOP_OTHER_CURVE 137 
#define  SSL_SECOP_OTHER_DH 136 
#define  SSL_SECOP_OTHER_SIGALG 135 
 int SSL_SECOP_OTHER_TYPE ; 
#define  SSL_SECOP_PEER_CA_MD 134 
#define  SSL_SECOP_SIGALG_CHECK 133 
#define  SSL_SECOP_SIGALG_MASK 132 
#define  SSL_SECOP_SIGALG_SHARED 131 
#define  SSL_SECOP_SIGALG_SUPPORTED 130 
#define  SSL_SECOP_TICKET 129 
#define  SSL_SECOP_VERSION 128 
 int /*<<< orphan*/ * X509_get0_pubkey (void*) ; 
 int X509_get_signature_nid (void*) ; 
 int /*<<< orphan*/  callback_types ; 
 char* lookup (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signature_tls12_alg_list ; 
 int /*<<< orphan*/  signature_tls12_hash_list ; 
 int /*<<< orphan*/  signature_tls13_scheme_list ; 
 int /*<<< orphan*/  ssl_versions ; 
 int stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int,void*,void*) ; 

__attribute__((used)) static int security_callback_debug(const SSL *s, const SSL_CTX *ctx,
                                   int op, int bits, int nid,
                                   void *other, void *ex)
{
    security_debug_ex *sdb = ex;
    int rv, show_bits = 1, cert_md = 0;
    const char *nm;
    int show_nm;
    rv = sdb->old_cb(s, ctx, op, bits, nid, other, ex);
    if (rv == 1 && sdb->verbose < 2)
        return 1;
    BIO_puts(sdb->out, "Security callback: ");

    nm = lookup(op, callback_types, NULL);
    show_nm = nm != NULL;
    switch (op) {
    case SSL_SECOP_TICKET:
    case SSL_SECOP_COMPRESSION:
        show_bits = 0;
        show_nm = 0;
        break;
    case SSL_SECOP_VERSION:
        BIO_printf(sdb->out, "Version=%s", lookup(nid, ssl_versions, "???"));
        show_bits = 0;
        show_nm = 0;
        break;
    case SSL_SECOP_CA_MD:
    case SSL_SECOP_PEER_CA_MD:
        cert_md = 1;
        break;
    case SSL_SECOP_SIGALG_SUPPORTED:
    case SSL_SECOP_SIGALG_SHARED:
    case SSL_SECOP_SIGALG_CHECK:
    case SSL_SECOP_SIGALG_MASK:
        show_nm = 0;
        break;
    }
    if (show_nm)
        BIO_printf(sdb->out, "%s=", nm);

    switch (op & SSL_SECOP_OTHER_TYPE) {

    case SSL_SECOP_OTHER_CIPHER:
        BIO_puts(sdb->out, SSL_CIPHER_get_name(other));
        break;

#ifndef OPENSSL_NO_EC
    case SSL_SECOP_OTHER_CURVE:
        {
            const char *cname;
            cname = EC_curve_nid2nist(nid);
            if (cname == NULL)
                cname = OBJ_nid2sn(nid);
            BIO_puts(sdb->out, cname);
        }
        break;
#endif
#ifndef OPENSSL_NO_DH
    case SSL_SECOP_OTHER_DH:
        {
            DH *dh = other;
            BIO_printf(sdb->out, "%d", DH_bits(dh));
            break;
        }
#endif
    case SSL_SECOP_OTHER_CERT:
        {
            if (cert_md) {
                int sig_nid = X509_get_signature_nid(other);
                BIO_puts(sdb->out, OBJ_nid2sn(sig_nid));
            } else {
                EVP_PKEY *pkey = X509_get0_pubkey(other);
                const char *algname = "";
                EVP_PKEY_asn1_get0_info(NULL, NULL, NULL, NULL,
                                        &algname, EVP_PKEY_get0_asn1(pkey));
                BIO_printf(sdb->out, "%s, bits=%d",
                           algname, EVP_PKEY_bits(pkey));
            }
            break;
        }
    case SSL_SECOP_OTHER_SIGALG:
        {
            const unsigned char *salg = other;
            const char *sname = NULL;
            int raw_sig_code = (salg[0] << 8) + salg[1]; /* always big endian (msb, lsb) */
                /* raw_sig_code: signature_scheme from tls1.3, or signature_and_hash from tls1.2 */

            if (nm != NULL)
                BIO_printf(sdb->out, "%s", nm);
            else
                BIO_printf(sdb->out, "s_cb.c:security_callback_debug op=0x%x", op);

            sname = lookup(raw_sig_code, signature_tls13_scheme_list, NULL);
            if (sname != NULL) {
                BIO_printf(sdb->out, " scheme=%s", sname);
            } else {
                int alg_code = salg[1];
                int hash_code = salg[0];
                const char *alg_str = lookup(alg_code, signature_tls12_alg_list, NULL);
                const char *hash_str = lookup(hash_code, signature_tls12_hash_list, NULL);

                if (alg_str != NULL && hash_str != NULL)
                    BIO_printf(sdb->out, " digest=%s, algorithm=%s", hash_str, alg_str);
                else
                    BIO_printf(sdb->out, " scheme=unknown(0x%04x)", raw_sig_code);
            }
        }

    }

    if (show_bits)
        BIO_printf(sdb->out, ", security bits=%d", bits);
    BIO_printf(sdb->out, ": %s\n", rv ? "yes" : "no");
    return rv;
}