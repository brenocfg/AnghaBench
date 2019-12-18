#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  rlayer; int /*<<< orphan*/ * expand; TYPE_2__* method; int /*<<< orphan*/ * enc_read_ctx; scalar_t__ read_hash; int /*<<< orphan*/ * session; } ;
struct TYPE_22__ {unsigned char* input; size_t length; unsigned char* data; size_t orig_len; scalar_t__ off; } ;
struct TYPE_21__ {TYPE_1__* ssl3_enc; } ;
struct TYPE_20__ {int (* mac ) (TYPE_4__*,TYPE_3__*,unsigned char*,int /*<<< orphan*/ ) ;int (* enc ) (TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  TYPE_3__ SSL3_RECORD ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  DTLS1_BITMAP ;

/* Variables and functions */
 scalar_t__ CRYPTO_memcmp (unsigned char*,unsigned char*,size_t) ; 
 size_t DTLS1_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  ERR_LIB_EVP ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_CIPHER_CTX_mode (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPH_CBC_MODE ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/ * EVP_MD_CTX_md (scalar_t__) ; 
 void* EVP_MD_CTX_size (scalar_t__) ; 
 unsigned char* RECORD_LAYER_get_packet (int /*<<< orphan*/ *) ; 
 TYPE_3__* RECORD_LAYER_get_rrec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_packet_length (int /*<<< orphan*/ *) ; 
 size_t SSL3_RT_MAX_COMPRESSED_LENGTH ; 
 size_t SSL3_RT_MAX_ENCRYPTED_LENGTH ; 
 size_t SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_AD_BAD_RECORD_MAC ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_DECOMPRESSION_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_RECORD_OVERFLOW ; 
 int /*<<< orphan*/  SSL_F_DTLS1_PROCESS_RECORD ; 
 scalar_t__ SSL_READ_ETM (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_R_BAD_DECOMPRESSION ; 
 int /*<<< orphan*/  SSL_R_COMPRESSED_LENGTH_TOO_LONG ; 
 int /*<<< orphan*/  SSL_R_DATA_LENGTH_TOO_LONG ; 
 int /*<<< orphan*/  SSL_R_DECRYPTION_FAILED_OR_BAD_RECORD_MAC ; 
 int /*<<< orphan*/  SSL_R_ENCRYPTED_LENGTH_TOO_LONG ; 
 int /*<<< orphan*/  SSL_R_LENGTH_TOO_SHORT ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtls1_record_bitmap_update (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 scalar_t__ ossl_statem_in_error (TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ssl3_cbc_copy_mac (unsigned char*,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  ssl3_do_uncompress (TYPE_4__*,TYPE_3__*) ; 
 int stub1 (TYPE_4__*,TYPE_3__*,unsigned char*,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int stub3 (TYPE_4__*,TYPE_3__*,unsigned char*,int /*<<< orphan*/ ) ; 

int dtls1_process_record(SSL *s, DTLS1_BITMAP *bitmap)
{
    int i;
    int enc_err;
    SSL_SESSION *sess;
    SSL3_RECORD *rr;
    int imac_size;
    size_t mac_size;
    unsigned char md[EVP_MAX_MD_SIZE];

    rr = RECORD_LAYER_get_rrec(&s->rlayer);
    sess = s->session;

    /*
     * At this point, s->packet_length == SSL3_RT_HEADER_LNGTH + rr->length,
     * and we have that many bytes in s->packet
     */
    rr->input = &(RECORD_LAYER_get_packet(&s->rlayer)[DTLS1_RT_HEADER_LENGTH]);

    /*
     * ok, we can now read from 's->packet' data into 'rr' rr->input points
     * at rr->length bytes, which need to be copied into rr->data by either
     * the decryption or by the decompression When the data is 'copied' into
     * the rr->data buffer, rr->input will be pointed at the new buffer
     */

    /*
     * We now have - encrypted [ MAC [ compressed [ plain ] ] ] rr->length
     * bytes of encrypted compressed stuff.
     */

    /* check is not needed I believe */
    if (rr->length > SSL3_RT_MAX_ENCRYPTED_LENGTH) {
        SSLfatal(s, SSL_AD_RECORD_OVERFLOW, SSL_F_DTLS1_PROCESS_RECORD,
                 SSL_R_ENCRYPTED_LENGTH_TOO_LONG);
        return 0;
    }

    /* decrypt in place in 'rr->input' */
    rr->data = rr->input;
    rr->orig_len = rr->length;

    if (SSL_READ_ETM(s) && s->read_hash) {
        unsigned char *mac;
        mac_size = EVP_MD_CTX_size(s->read_hash);
        if (!ossl_assert(mac_size <= EVP_MAX_MD_SIZE)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DTLS1_PROCESS_RECORD,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
        if (rr->orig_len < mac_size) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_DTLS1_PROCESS_RECORD,
                     SSL_R_LENGTH_TOO_SHORT);
            return 0;
        }
        rr->length -= mac_size;
        mac = rr->data + rr->length;
        i = s->method->ssl3_enc->mac(s, rr, md, 0 /* not send */ );
        if (i == 0 || CRYPTO_memcmp(md, mac, (size_t)mac_size) != 0) {
            SSLfatal(s, SSL_AD_BAD_RECORD_MAC, SSL_F_DTLS1_PROCESS_RECORD,
                   SSL_R_DECRYPTION_FAILED_OR_BAD_RECORD_MAC);
            return 0;
        }
    }

    enc_err = s->method->ssl3_enc->enc(s, rr, 1, 0);
    /*-
     * enc_err is:
     *    0: (in non-constant time) if the record is publically invalid.
     *    1: if the padding is valid
     *   -1: if the padding is invalid
     */
    if (enc_err == 0) {
        if (ossl_statem_in_error(s)) {
            /* SSLfatal() got called */
            return 0;
        }
        /* For DTLS we simply ignore bad packets. */
        rr->length = 0;
        RECORD_LAYER_reset_packet_length(&s->rlayer);
        return 0;
    }
#ifdef SSL_DEBUG
    printf("dec %ld\n", rr->length);
    {
        size_t z;
        for (z = 0; z < rr->length; z++)
            printf("%02X%c", rr->data[z], ((z + 1) % 16) ? ' ' : '\n');
    }
    printf("\n");
#endif

    /* r->length is now the compressed data plus mac */
    if ((sess != NULL) && !SSL_READ_ETM(s) &&
        (s->enc_read_ctx != NULL) && (EVP_MD_CTX_md(s->read_hash) != NULL)) {
        /* s->read_hash != NULL => mac_size != -1 */
        unsigned char *mac = NULL;
        unsigned char mac_tmp[EVP_MAX_MD_SIZE];

        /* TODO(size_t): Convert this to do size_t properly */
        imac_size = EVP_MD_CTX_size(s->read_hash);
        if (imac_size < 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DTLS1_PROCESS_RECORD,
                     ERR_LIB_EVP);
            return 0;
        }
        mac_size = (size_t)imac_size;
        if (!ossl_assert(mac_size <= EVP_MAX_MD_SIZE)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DTLS1_PROCESS_RECORD,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }

        /*
         * orig_len is the length of the record before any padding was
         * removed. This is public information, as is the MAC in use,
         * therefore we can safely process the record in a different amount
         * of time if it's too short to possibly contain a MAC.
         */
        if (rr->orig_len < mac_size ||
            /* CBC records must have a padding length byte too. */
            (EVP_CIPHER_CTX_mode(s->enc_read_ctx) == EVP_CIPH_CBC_MODE &&
             rr->orig_len < mac_size + 1)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_DTLS1_PROCESS_RECORD,
                     SSL_R_LENGTH_TOO_SHORT);
            return 0;
        }

        if (EVP_CIPHER_CTX_mode(s->enc_read_ctx) == EVP_CIPH_CBC_MODE) {
            /*
             * We update the length so that the TLS header bytes can be
             * constructed correctly but we need to extract the MAC in
             * constant time from within the record, without leaking the
             * contents of the padding bytes.
             */
            mac = mac_tmp;
            if (!ssl3_cbc_copy_mac(mac_tmp, rr, mac_size)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DTLS1_PROCESS_RECORD,
                         ERR_R_INTERNAL_ERROR);
                return 0;
            }
            rr->length -= mac_size;
        } else {
            /*
             * In this case there's no padding, so |rec->orig_len| equals
             * |rec->length| and we checked that there's enough bytes for
             * |mac_size| above.
             */
            rr->length -= mac_size;
            mac = &rr->data[rr->length];
        }

        i = s->method->ssl3_enc->mac(s, rr, md, 0 /* not send */ );
        if (i == 0 || mac == NULL
            || CRYPTO_memcmp(md, mac, mac_size) != 0)
            enc_err = -1;
        if (rr->length > SSL3_RT_MAX_COMPRESSED_LENGTH + mac_size)
            enc_err = -1;
    }

    if (enc_err < 0) {
        /* decryption failed, silently discard message */
        rr->length = 0;
        RECORD_LAYER_reset_packet_length(&s->rlayer);
        return 0;
    }

    /* r->length is now just compressed */
    if (s->expand != NULL) {
        if (rr->length > SSL3_RT_MAX_COMPRESSED_LENGTH) {
            SSLfatal(s, SSL_AD_RECORD_OVERFLOW, SSL_F_DTLS1_PROCESS_RECORD,
                     SSL_R_COMPRESSED_LENGTH_TOO_LONG);
            return 0;
        }
        if (!ssl3_do_uncompress(s, rr)) {
            SSLfatal(s, SSL_AD_DECOMPRESSION_FAILURE,
                     SSL_F_DTLS1_PROCESS_RECORD, SSL_R_BAD_DECOMPRESSION);
            return 0;
        }
    }

    if (rr->length > SSL3_RT_MAX_PLAIN_LENGTH) {
        SSLfatal(s, SSL_AD_RECORD_OVERFLOW, SSL_F_DTLS1_PROCESS_RECORD,
                 SSL_R_DATA_LENGTH_TOO_LONG);
        return 0;
    }

    rr->off = 0;
    /*-
     * So at this point the following is true
     * ssl->s3->rrec.type   is the type of record
     * ssl->s3->rrec.length == number of bytes in record
     * ssl->s3->rrec.off    == offset to first valid byte
     * ssl->s3->rrec.data   == where to take bytes from, increment
     *                         after use :-).
     */

    /* we have pulled in a full packet so zero things */
    RECORD_LAYER_reset_packet_length(&s->rlayer);

    /* Mark receipt of record. */
    dtls1_record_bitmap_update(s, bitmap);

    return 1;
}