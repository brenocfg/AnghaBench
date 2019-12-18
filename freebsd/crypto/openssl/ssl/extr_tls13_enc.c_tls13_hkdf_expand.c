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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  label_prefix ;
typedef  int /*<<< orphan*/  hkdflabel ;
typedef  int /*<<< orphan*/  WPACKET ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int EVP_MAX_MD_SIZE ; 
 size_t EVP_MD_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_add1_hkdf_info (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_hkdf_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set1_hkdf_key (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 scalar_t__ EVP_PKEY_CTX_set_hkdf_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_HKDEF_MODE_EXPAND_ONLY ; 
 int /*<<< orphan*/  EVP_PKEY_HKDF ; 
 scalar_t__ EVP_PKEY_derive (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_PKEY_derive_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS13_HKDF_EXPAND ; 
 int /*<<< orphan*/  SSL_R_TLS_ILLEGAL_EXPORTER_LABEL ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS13_MAX_LABEL_LEN ; 
 int /*<<< orphan*/  WPACKET_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_init_static_len (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int tls13_hkdf_expand(SSL *s, const EVP_MD *md, const unsigned char *secret,
                             const unsigned char *label, size_t labellen,
                             const unsigned char *data, size_t datalen,
                             unsigned char *out, size_t outlen, int fatal)
{
#ifdef CHARSET_EBCDIC
    static const unsigned char label_prefix[] = { 0x74, 0x6C, 0x73, 0x31, 0x33, 0x20, 0x00 };
#else
    static const unsigned char label_prefix[] = "tls13 ";
#endif
    EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_HKDF, NULL);
    int ret;
    size_t hkdflabellen;
    size_t hashlen;
    /*
     * 2 bytes for length of derived secret + 1 byte for length of combined
     * prefix and label + bytes for the label itself + 1 byte length of hash
     * + bytes for the hash itself
     */
    unsigned char hkdflabel[sizeof(uint16_t) + sizeof(uint8_t) +
                            + (sizeof(label_prefix) - 1) + TLS13_MAX_LABEL_LEN
                            + 1 + EVP_MAX_MD_SIZE];
    WPACKET pkt;

    if (pctx == NULL)
        return 0;

    if (labellen > TLS13_MAX_LABEL_LEN) {
        if (fatal) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_HKDF_EXPAND,
                     ERR_R_INTERNAL_ERROR);
        } else {
            /*
             * Probably we have been called from SSL_export_keying_material(),
             * or SSL_export_keying_material_early().
             */
            SSLerr(SSL_F_TLS13_HKDF_EXPAND, SSL_R_TLS_ILLEGAL_EXPORTER_LABEL);
        }
        EVP_PKEY_CTX_free(pctx);
        return 0;
    }

    hashlen = EVP_MD_size(md);

    if (!WPACKET_init_static_len(&pkt, hkdflabel, sizeof(hkdflabel), 0)
            || !WPACKET_put_bytes_u16(&pkt, outlen)
            || !WPACKET_start_sub_packet_u8(&pkt)
            || !WPACKET_memcpy(&pkt, label_prefix, sizeof(label_prefix) - 1)
            || !WPACKET_memcpy(&pkt, label, labellen)
            || !WPACKET_close(&pkt)
            || !WPACKET_sub_memcpy_u8(&pkt, data, (data == NULL) ? 0 : datalen)
            || !WPACKET_get_total_written(&pkt, &hkdflabellen)
            || !WPACKET_finish(&pkt)) {
        EVP_PKEY_CTX_free(pctx);
        WPACKET_cleanup(&pkt);
        if (fatal)
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_HKDF_EXPAND,
                     ERR_R_INTERNAL_ERROR);
        else
            SSLerr(SSL_F_TLS13_HKDF_EXPAND, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    ret = EVP_PKEY_derive_init(pctx) <= 0
            || EVP_PKEY_CTX_hkdf_mode(pctx, EVP_PKEY_HKDEF_MODE_EXPAND_ONLY)
               <= 0
            || EVP_PKEY_CTX_set_hkdf_md(pctx, md) <= 0
            || EVP_PKEY_CTX_set1_hkdf_key(pctx, secret, hashlen) <= 0
            || EVP_PKEY_CTX_add1_hkdf_info(pctx, hkdflabel, hkdflabellen) <= 0
            || EVP_PKEY_derive(pctx, out, &outlen) <= 0;

    EVP_PKEY_CTX_free(pctx);

    if (ret != 0) {
        if (fatal)
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_HKDF_EXPAND,
                     ERR_R_INTERNAL_ERROR);
        else
            SSLerr(SSL_F_TLS13_HKDF_EXPAND, ERR_R_INTERNAL_ERROR);
    }

    return ret == 0;
}