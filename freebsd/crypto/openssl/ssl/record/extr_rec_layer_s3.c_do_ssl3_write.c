#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_41__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wr ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_45__ {size_t numwpipes; size_t wpend_tot; unsigned char const* wpend_buf; int wpend_type; size_t wpend_ret; int /*<<< orphan*/ * wbuf; } ;
struct TYPE_43__ {scalar_t__ enc_write_state; } ;
struct TYPE_48__ {unsigned int version; scalar_t__ hello_retry_request; size_t (* record_padding_cb ) (TYPE_6__*,int,size_t,int /*<<< orphan*/ ) ;int block_padding; TYPE_41__ rlayer; int /*<<< orphan*/  msg_callback_arg; int /*<<< orphan*/  (* msg_callback ) (int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int,TYPE_6__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * enc_write_ctx; TYPE_4__* method; TYPE_2__ statem; int /*<<< orphan*/  record_padding_arg; int /*<<< orphan*/ * compress; int /*<<< orphan*/  renegotiate; TYPE_1__* s3; int /*<<< orphan*/  write_hash; int /*<<< orphan*/ * session; } ;
struct TYPE_47__ {int length; int /*<<< orphan*/  input; } ;
struct TYPE_46__ {int (* ssl_dispatch_alert ) (TYPE_6__*) ;TYPE_3__* ssl3_enc; } ;
struct TYPE_44__ {int (* enc ) (TYPE_6__*,TYPE_5__*,size_t,int) ;int /*<<< orphan*/  (* mac ) (TYPE_6__*,TYPE_5__*,unsigned char*,int) ;} ;
struct TYPE_42__ {int empty_fragment_done; scalar_t__ need_empty_fragments; scalar_t__ alert_dispatch; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  TYPE_5__ SSL3_RECORD ;
typedef  int /*<<< orphan*/  SSL3_BUFFER ;
typedef  TYPE_6__ SSL ;

/* Variables and functions */
 scalar_t__ ENC_WRITE_STATE_WRITE_PLAIN_ALERTS ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int EVP_CCM_TLS_EXPLICIT_IV_LEN ; 
 int EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_mode (int /*<<< orphan*/ *) ; 
 int EVP_CIPH_CBC_MODE ; 
 int EVP_CIPH_CCM_MODE ; 
 int EVP_CIPH_GCM_MODE ; 
 int EVP_GCM_TLS_EXPLICIT_IV_LEN ; 
 int /*<<< orphan*/ * EVP_MD_CTX_md (int /*<<< orphan*/ ) ; 
 int EVP_MD_CTX_size (int /*<<< orphan*/ ) ; 
 scalar_t__ RECORD_LAYER_write_pending (TYPE_41__*) ; 
 int SSL3_ALIGN_PAYLOAD ; 
 scalar_t__ SSL3_BUFFER_get_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_BUFFER_get_len (int /*<<< orphan*/ *) ; 
 size_t SSL3_BUFFER_get_offset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_BUFFER_set_left (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SSL3_BUFFER_set_offset (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SSL3_RECORD_add_length (TYPE_5__*,size_t) ; 
 size_t SSL3_RECORD_get_length (TYPE_5__*) ; 
 int /*<<< orphan*/  SSL3_RECORD_reset_input (TYPE_5__*) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_data (TYPE_5__*,unsigned char*) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_input (TYPE_5__*,unsigned char*) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_length (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_rec_version (TYPE_5__*,unsigned int) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_type (TYPE_5__*,int) ; 
 int SSL3_RT_ALERT ; 
 int SSL3_RT_APPLICATION_DATA ; 
 int /*<<< orphan*/  SSL3_RT_HEADER ; 
 size_t SSL3_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  SSL3_RT_INNER_CONTENT_TYPE ; 
 scalar_t__ SSL3_RT_MAX_COMPRESSED_OVERHEAD ; 
 size_t SSL3_RT_SEND_MAX_ENCRYPTED_OVERHEAD ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_DO_SSL3_WRITE ; 
 scalar_t__ SSL_HRR_NONE ; 
 int SSL_MAX_PIPELINES ; 
 size_t SSL_RT_MAX_CIPHER_BLOCK_SIZE ; 
 int /*<<< orphan*/  SSL_R_COMPRESSION_FAILURE ; 
 scalar_t__ SSL_TREAT_AS_TLS13 (TYPE_6__*) ; 
 scalar_t__ SSL_USE_EXPLICIT_IV (TYPE_6__*) ; 
 scalar_t__ SSL_WRITE_ETM (TYPE_6__*) ; 
 scalar_t__ SSL_get_state (TYPE_6__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int TLS1_2_VERSION ; 
 unsigned int TLS1_3_VERSION ; 
 unsigned int TLS1_VERSION ; 
 unsigned int TLS1_get_version (TYPE_6__*) ; 
 scalar_t__ TLS_ST_CW_CLNT_HELLO ; 
 int /*<<< orphan*/  WPACKET_allocate_bytes (int /*<<< orphan*/ *,int,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_finish (int /*<<< orphan*/ *) ; 
 size_t WPACKET_get_curr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_length (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_init_static_len (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WPACKET_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPACKET_reserve_bytes (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_statem_in_error (TYPE_6__*) ; 
 int /*<<< orphan*/  ssl3_do_compress (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ssl3_setup_write_buffer (TYPE_6__*,size_t,int /*<<< orphan*/ ) ; 
 int ssl3_write_pending (TYPE_6__*,int,unsigned char const*,size_t,size_t*) ; 
 size_t ssl_get_max_send_fragment (TYPE_6__*) ; 
 int stub1 (TYPE_6__*) ; 
 size_t stub2 (TYPE_6__*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,TYPE_5__*,unsigned char*,int) ; 
 int stub4 (TYPE_6__*,TYPE_5__*,size_t,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,TYPE_5__*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub6 (int,unsigned int,int /*<<< orphan*/ ,unsigned char*,size_t,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int tls13_enc (TYPE_6__*,TYPE_5__*,size_t,int) ; 

int do_ssl3_write(SSL *s, int type, const unsigned char *buf,
                  size_t *pipelens, size_t numpipes,
                  int create_empty_fragment, size_t *written)
{
    WPACKET pkt[SSL_MAX_PIPELINES];
    SSL3_RECORD wr[SSL_MAX_PIPELINES];
    WPACKET *thispkt;
    SSL3_RECORD *thiswr;
    unsigned char *recordstart;
    int i, mac_size, clear = 0;
    size_t prefix_len = 0;
    int eivlen = 0;
    size_t align = 0;
    SSL3_BUFFER *wb;
    SSL_SESSION *sess;
    size_t totlen = 0, len, wpinited = 0;
    size_t j;

    for (j = 0; j < numpipes; j++)
        totlen += pipelens[j];
    /*
     * first check if there is a SSL3_BUFFER still being written out.  This
     * will happen with non blocking IO
     */
    if (RECORD_LAYER_write_pending(&s->rlayer)) {
        /* Calls SSLfatal() as required */
        return ssl3_write_pending(s, type, buf, totlen, written);
    }

    /* If we have an alert to send, lets send it */
    if (s->s3->alert_dispatch) {
        i = s->method->ssl_dispatch_alert(s);
        if (i <= 0) {
            /* SSLfatal() already called if appropriate */
            return i;
        }
        /* if it went, fall through and send more stuff */
    }

    if (s->rlayer.numwpipes < numpipes) {
        if (!ssl3_setup_write_buffer(s, numpipes, 0)) {
            /* SSLfatal() already called */
            return -1;
        }
    }

    if (totlen == 0 && !create_empty_fragment)
        return 0;

    sess = s->session;

    if ((sess == NULL) ||
        (s->enc_write_ctx == NULL) || (EVP_MD_CTX_md(s->write_hash) == NULL)) {
        clear = s->enc_write_ctx ? 0 : 1; /* must be AEAD cipher */
        mac_size = 0;
    } else {
        /* TODO(siz_t): Convert me */
        mac_size = EVP_MD_CTX_size(s->write_hash);
        if (mac_size < 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
    }

    /*
     * 'create_empty_fragment' is true only when this function calls itself
     */
    if (!clear && !create_empty_fragment && !s->s3->empty_fragment_done) {
        /*
         * countermeasure against known-IV weakness in CBC ciphersuites (see
         * http://www.openssl.org/~bodo/tls-cbc.txt)
         */

        if (s->s3->need_empty_fragments && type == SSL3_RT_APPLICATION_DATA) {
            /*
             * recursive function call with 'create_empty_fragment' set; this
             * prepares and buffers the data for an empty fragment (these
             * 'prefix_len' bytes are sent out later together with the actual
             * payload)
             */
            size_t tmppipelen = 0;
            int ret;

            ret = do_ssl3_write(s, type, buf, &tmppipelen, 1, 1, &prefix_len);
            if (ret <= 0) {
                /* SSLfatal() already called if appropriate */
                goto err;
            }

            if (prefix_len >
                (SSL3_RT_HEADER_LENGTH + SSL3_RT_SEND_MAX_ENCRYPTED_OVERHEAD)) {
                /* insufficient space */
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
        }

        s->s3->empty_fragment_done = 1;
    }

    if (create_empty_fragment) {
        wb = &s->rlayer.wbuf[0];
#if defined(SSL3_ALIGN_PAYLOAD) && SSL3_ALIGN_PAYLOAD!=0
        /*
         * extra fragment would be couple of cipher blocks, which would be
         * multiple of SSL3_ALIGN_PAYLOAD, so if we want to align the real
         * payload, then we can just pretend we simply have two headers.
         */
        align = (size_t)SSL3_BUFFER_get_buf(wb) + 2 * SSL3_RT_HEADER_LENGTH;
        align = SSL3_ALIGN_PAYLOAD - 1 - ((align - 1) % SSL3_ALIGN_PAYLOAD);
#endif
        SSL3_BUFFER_set_offset(wb, align);
        if (!WPACKET_init_static_len(&pkt[0], SSL3_BUFFER_get_buf(wb),
                                     SSL3_BUFFER_get_len(wb), 0)
                || !WPACKET_allocate_bytes(&pkt[0], align, NULL)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        wpinited = 1;
    } else if (prefix_len) {
        wb = &s->rlayer.wbuf[0];
        if (!WPACKET_init_static_len(&pkt[0],
                                     SSL3_BUFFER_get_buf(wb),
                                     SSL3_BUFFER_get_len(wb), 0)
                || !WPACKET_allocate_bytes(&pkt[0], SSL3_BUFFER_get_offset(wb)
                                                    + prefix_len, NULL)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        wpinited = 1;
    } else {
        for (j = 0; j < numpipes; j++) {
            thispkt = &pkt[j];

            wb = &s->rlayer.wbuf[j];
#if defined(SSL3_ALIGN_PAYLOAD) && SSL3_ALIGN_PAYLOAD != 0
            align = (size_t)SSL3_BUFFER_get_buf(wb) + SSL3_RT_HEADER_LENGTH;
            align = SSL3_ALIGN_PAYLOAD - 1 - ((align - 1) % SSL3_ALIGN_PAYLOAD);
#endif
            SSL3_BUFFER_set_offset(wb, align);
            if (!WPACKET_init_static_len(thispkt, SSL3_BUFFER_get_buf(wb),
                                         SSL3_BUFFER_get_len(wb), 0)
                    || !WPACKET_allocate_bytes(thispkt, align, NULL)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
            wpinited++;
        }
    }

    /* Explicit IV length, block ciphers appropriate version flag */
    if (s->enc_write_ctx && SSL_USE_EXPLICIT_IV(s) && !SSL_TREAT_AS_TLS13(s)) {
        int mode = EVP_CIPHER_CTX_mode(s->enc_write_ctx);
        if (mode == EVP_CIPH_CBC_MODE) {
            /* TODO(size_t): Convert me */
            eivlen = EVP_CIPHER_CTX_iv_length(s->enc_write_ctx);
            if (eivlen <= 1)
                eivlen = 0;
        } else if (mode == EVP_CIPH_GCM_MODE) {
            /* Need explicit part of IV for GCM mode */
            eivlen = EVP_GCM_TLS_EXPLICIT_IV_LEN;
        } else if (mode == EVP_CIPH_CCM_MODE) {
            eivlen = EVP_CCM_TLS_EXPLICIT_IV_LEN;
        }
    }

    totlen = 0;
    /* Clear our SSL3_RECORD structures */
    memset(wr, 0, sizeof(wr));
    for (j = 0; j < numpipes; j++) {
        unsigned int version = (s->version == TLS1_3_VERSION) ? TLS1_2_VERSION
                                                              : s->version;
        unsigned char *compressdata = NULL;
        size_t maxcomplen;
        unsigned int rectype;

        thispkt = &pkt[j];
        thiswr = &wr[j];

        /*
         * In TLSv1.3, once encrypting, we always use application data for the
         * record type
         */
        if (SSL_TREAT_AS_TLS13(s)
                && s->enc_write_ctx != NULL
                && (s->statem.enc_write_state != ENC_WRITE_STATE_WRITE_PLAIN_ALERTS
                    || type != SSL3_RT_ALERT))
            rectype = SSL3_RT_APPLICATION_DATA;
        else
            rectype = type;
        SSL3_RECORD_set_type(thiswr, rectype);

        /*
         * Some servers hang if initial client hello is larger than 256 bytes
         * and record version number > TLS 1.0
         */
        if (SSL_get_state(s) == TLS_ST_CW_CLNT_HELLO
                && !s->renegotiate
                && TLS1_get_version(s) > TLS1_VERSION
                && s->hello_retry_request == SSL_HRR_NONE)
            version = TLS1_VERSION;
        SSL3_RECORD_set_rec_version(thiswr, version);

        maxcomplen = pipelens[j];
        if (s->compress != NULL)
            maxcomplen += SSL3_RT_MAX_COMPRESSED_OVERHEAD;

        /* write the header */
        if (!WPACKET_put_bytes_u8(thispkt, rectype)
                || !WPACKET_put_bytes_u16(thispkt, version)
                || !WPACKET_start_sub_packet_u16(thispkt)
                || (eivlen > 0
                    && !WPACKET_allocate_bytes(thispkt, eivlen, NULL))
                || (maxcomplen > 0
                    && !WPACKET_reserve_bytes(thispkt, maxcomplen,
                                              &compressdata))) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        /* lets setup the record stuff. */
        SSL3_RECORD_set_data(thiswr, compressdata);
        SSL3_RECORD_set_length(thiswr, pipelens[j]);
        SSL3_RECORD_set_input(thiswr, (unsigned char *)&buf[totlen]);
        totlen += pipelens[j];

        /*
         * we now 'read' from thiswr->input, thiswr->length bytes into
         * thiswr->data
         */

        /* first we compress */
        if (s->compress != NULL) {
            if (!ssl3_do_compress(s, thiswr)
                    || !WPACKET_allocate_bytes(thispkt, thiswr->length, NULL)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         SSL_R_COMPRESSION_FAILURE);
                goto err;
            }
        } else {
            if (!WPACKET_memcpy(thispkt, thiswr->input, thiswr->length)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
            SSL3_RECORD_reset_input(&wr[j]);
        }

        if (SSL_TREAT_AS_TLS13(s)
                && s->enc_write_ctx != NULL
                && (s->statem.enc_write_state != ENC_WRITE_STATE_WRITE_PLAIN_ALERTS
                    || type != SSL3_RT_ALERT)) {
            size_t rlen, max_send_fragment;

            if (!WPACKET_put_bytes_u8(thispkt, type)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
            SSL3_RECORD_add_length(thiswr, 1);

            /* Add TLS1.3 padding */
            max_send_fragment = ssl_get_max_send_fragment(s);
            rlen = SSL3_RECORD_get_length(thiswr);
            if (rlen < max_send_fragment) {
                size_t padding = 0;
                size_t max_padding = max_send_fragment - rlen;
                if (s->record_padding_cb != NULL) {
                    padding = s->record_padding_cb(s, type, rlen, s->record_padding_arg);
                } else if (s->block_padding > 0) {
                    size_t mask = s->block_padding - 1;
                    size_t remainder;

                    /* optimize for power of 2 */
                    if ((s->block_padding & mask) == 0)
                        remainder = rlen & mask;
                    else
                        remainder = rlen % s->block_padding;
                    /* don't want to add a block of padding if we don't have to */
                    if (remainder == 0)
                        padding = 0;
                    else
                        padding = s->block_padding - remainder;
                }
                if (padding > 0) {
                    /* do not allow the record to exceed max plaintext length */
                    if (padding > max_padding)
                        padding = max_padding;
                    if (!WPACKET_memset(thispkt, 0, padding)) {
                        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                                 ERR_R_INTERNAL_ERROR);
                        goto err;
                    }
                    SSL3_RECORD_add_length(thiswr, padding);
                }
            }
        }

        /*
         * we should still have the output to thiswr->data and the input from
         * wr->input. Length should be thiswr->length. thiswr->data still points
         * in the wb->buf
         */

        if (!SSL_WRITE_ETM(s) && mac_size != 0) {
            unsigned char *mac;

            if (!WPACKET_allocate_bytes(thispkt, mac_size, &mac)
                    || !s->method->ssl3_enc->mac(s, thiswr, mac, 1)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
        }

        /*
         * Reserve some bytes for any growth that may occur during encryption.
         * This will be at most one cipher block or the tag length if using
         * AEAD. SSL_RT_MAX_CIPHER_BLOCK_SIZE covers either case.
         */
        if (!WPACKET_reserve_bytes(thispkt, SSL_RT_MAX_CIPHER_BLOCK_SIZE,
                                   NULL)
                   /*
                    * We also need next the amount of bytes written to this
                    * sub-packet
                    */
                || !WPACKET_get_length(thispkt, &len)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        /* Get a pointer to the start of this record excluding header */
        recordstart = WPACKET_get_curr(thispkt) - len;

        SSL3_RECORD_set_data(thiswr, recordstart);
        SSL3_RECORD_reset_input(thiswr);
        SSL3_RECORD_set_length(thiswr, len);
    }

    if (s->statem.enc_write_state == ENC_WRITE_STATE_WRITE_PLAIN_ALERTS) {
        /*
         * We haven't actually negotiated the version yet, but we're trying to
         * send early data - so we need to use the tls13enc function.
         */
        if (tls13_enc(s, wr, numpipes, 1) < 1) {
            if (!ossl_statem_in_error(s)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
            }
            goto err;
        }
    } else {
        if (s->method->ssl3_enc->enc(s, wr, numpipes, 1) < 1) {
            if (!ossl_statem_in_error(s)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
            }
            goto err;
        }
    }

    for (j = 0; j < numpipes; j++) {
        size_t origlen;

        thispkt = &pkt[j];
        thiswr = &wr[j];

        /* Allocate bytes for the encryption overhead */
        if (!WPACKET_get_length(thispkt, &origlen)
                   /* Encryption should never shrink the data! */
                || origlen > thiswr->length
                || (thiswr->length > origlen
                    && !WPACKET_allocate_bytes(thispkt,
                                               thiswr->length - origlen, NULL))) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        if (SSL_WRITE_ETM(s) && mac_size != 0) {
            unsigned char *mac;

            if (!WPACKET_allocate_bytes(thispkt, mac_size, &mac)
                    || !s->method->ssl3_enc->mac(s, thiswr, mac, 1)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
            SSL3_RECORD_add_length(thiswr, mac_size);
        }

        if (!WPACKET_get_length(thispkt, &len)
                || !WPACKET_close(thispkt)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        if (s->msg_callback) {
            recordstart = WPACKET_get_curr(thispkt) - len
                          - SSL3_RT_HEADER_LENGTH;
            s->msg_callback(1, 0, SSL3_RT_HEADER, recordstart,
                            SSL3_RT_HEADER_LENGTH, s,
                            s->msg_callback_arg);

            if (SSL_TREAT_AS_TLS13(s) && s->enc_write_ctx != NULL) {
                unsigned char ctype = type;

                s->msg_callback(1, s->version, SSL3_RT_INNER_CONTENT_TYPE,
                                &ctype, 1, s, s->msg_callback_arg);
            }
        }

        if (!WPACKET_finish(thispkt)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        /*
         * we should now have thiswr->data pointing to the encrypted data, which
         * is thiswr->length long
         */
        SSL3_RECORD_set_type(thiswr, type); /* not needed but helps for
                                             * debugging */
        SSL3_RECORD_add_length(thiswr, SSL3_RT_HEADER_LENGTH);

        if (create_empty_fragment) {
            /*
             * we are in a recursive call; just return the length, don't write
             * out anything here
             */
            if (j > 0) {
                /* We should never be pipelining an empty fragment!! */
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DO_SSL3_WRITE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
            *written = SSL3_RECORD_get_length(thiswr);
            return 1;
        }

        /* now let's set up wb */
        SSL3_BUFFER_set_left(&s->rlayer.wbuf[j],
                             prefix_len + SSL3_RECORD_get_length(thiswr));
    }

    /*
     * memorize arguments so that ssl3_write_pending can detect bad write
     * retries later
     */
    s->rlayer.wpend_tot = totlen;
    s->rlayer.wpend_buf = buf;
    s->rlayer.wpend_type = type;
    s->rlayer.wpend_ret = totlen;

    /* we now just need to write the buffer */
    return ssl3_write_pending(s, type, buf, totlen, written);
 err:
    for (j = 0; j < wpinited; j++)
        WPACKET_cleanup(&pkt[j]);
    return -1;
}