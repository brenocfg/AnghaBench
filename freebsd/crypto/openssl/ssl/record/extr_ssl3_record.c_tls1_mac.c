#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
struct TYPE_10__ {int mac_flags; int version; TYPE_1__* s3; int /*<<< orphan*/  enc_read_ctx; int /*<<< orphan*/  rlayer; int /*<<< orphan*/ * read_hash; int /*<<< orphan*/ * write_hash; } ;
struct TYPE_9__ {unsigned char type; int length; unsigned char* input; int* data; int /*<<< orphan*/  orig_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  read_mac_secret_size; int /*<<< orphan*/  read_mac_secret; } ;
typedef  TYPE_2__ SSL3_RECORD ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DTLS_RECORD_LAYER_get_r_epoch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DTLS_RECORD_LAYER_get_w_epoch (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_CIPH_CBC_MODE ; 
 scalar_t__ EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_DigestSignUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_MD_CTX_size (int /*<<< orphan*/ *) ; 
 unsigned char* RECORD_LAYER_get_read_sequence (int /*<<< orphan*/ *) ; 
 unsigned char* RECORD_LAYER_get_write_sequence (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_IS_DTLS (TYPE_3__*) ; 
 int SSL_MAC_FLAG_READ_MAC_STREAM ; 
 int SSL_MAC_FLAG_WRITE_MAC_STREAM ; 
 int /*<<< orphan*/  SSL_READ_ETM (TYPE_3__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  s2n (int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ ssl3_cbc_digest_record (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssl3_cbc_record_digest_supported (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int tls1_mac(SSL *ssl, SSL3_RECORD *rec, unsigned char *md, int sending)
{
    unsigned char *seq;
    EVP_MD_CTX *hash;
    size_t md_size;
    int i;
    EVP_MD_CTX *hmac = NULL, *mac_ctx;
    unsigned char header[13];
    int stream_mac = (sending ? (ssl->mac_flags & SSL_MAC_FLAG_WRITE_MAC_STREAM)
                      : (ssl->mac_flags & SSL_MAC_FLAG_READ_MAC_STREAM));
    int t;

    if (sending) {
        seq = RECORD_LAYER_get_write_sequence(&ssl->rlayer);
        hash = ssl->write_hash;
    } else {
        seq = RECORD_LAYER_get_read_sequence(&ssl->rlayer);
        hash = ssl->read_hash;
    }

    t = EVP_MD_CTX_size(hash);
    if (!ossl_assert(t >= 0))
        return 0;
    md_size = t;

    /* I should fix this up TLS TLS TLS TLS TLS XXXXXXXX */
    if (stream_mac) {
        mac_ctx = hash;
    } else {
        hmac = EVP_MD_CTX_new();
        if (hmac == NULL || !EVP_MD_CTX_copy(hmac, hash)) {
            EVP_MD_CTX_free(hmac);
            return 0;
        }
        mac_ctx = hmac;
    }

    if (SSL_IS_DTLS(ssl)) {
        unsigned char dtlsseq[8], *p = dtlsseq;

        s2n(sending ? DTLS_RECORD_LAYER_get_w_epoch(&ssl->rlayer) :
            DTLS_RECORD_LAYER_get_r_epoch(&ssl->rlayer), p);
        memcpy(p, &seq[2], 6);

        memcpy(header, dtlsseq, 8);
    } else
        memcpy(header, seq, 8);

    header[8] = rec->type;
    header[9] = (unsigned char)(ssl->version >> 8);
    header[10] = (unsigned char)(ssl->version);
    header[11] = (unsigned char)(rec->length >> 8);
    header[12] = (unsigned char)(rec->length & 0xff);

    if (!sending && !SSL_READ_ETM(ssl) &&
        EVP_CIPHER_CTX_mode(ssl->enc_read_ctx) == EVP_CIPH_CBC_MODE &&
        ssl3_cbc_record_digest_supported(mac_ctx)) {
        /*
         * This is a CBC-encrypted record. We must avoid leaking any
         * timing-side channel information about how many blocks of data we
         * are hashing because that gives an attacker a timing-oracle.
         */
        /* Final param == not SSLv3 */
        if (ssl3_cbc_digest_record(mac_ctx,
                                   md, &md_size,
                                   header, rec->input,
                                   rec->length + md_size, rec->orig_len,
                                   ssl->s3->read_mac_secret,
                                   ssl->s3->read_mac_secret_size, 0) <= 0) {
            EVP_MD_CTX_free(hmac);
            return 0;
        }
    } else {
        /* TODO(size_t): Convert these calls */
        if (EVP_DigestSignUpdate(mac_ctx, header, sizeof(header)) <= 0
            || EVP_DigestSignUpdate(mac_ctx, rec->input, rec->length) <= 0
            || EVP_DigestSignFinal(mac_ctx, md, &md_size) <= 0) {
            EVP_MD_CTX_free(hmac);
            return 0;
        }
    }

    EVP_MD_CTX_free(hmac);

#ifdef SSL_DEBUG
    fprintf(stderr, "seq=");
    {
        int z;
        for (z = 0; z < 8; z++)
            fprintf(stderr, "%02X ", seq[z]);
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "rec=");
    {
        size_t z;
        for (z = 0; z < rec->length; z++)
            fprintf(stderr, "%02X ", rec->data[z]);
        fprintf(stderr, "\n");
    }
#endif

    if (!SSL_IS_DTLS(ssl)) {
        for (i = 7; i >= 0; i--) {
            ++seq[i];
            if (seq[i] != 0)
                break;
        }
    }
#ifdef SSL_DEBUG
    {
        unsigned int z;
        for (z = 0; z < md_size; z++)
            fprintf(stderr, "%02X ", md[z]);
        fprintf(stderr, "\n");
    }
#endif
    return 1;
}