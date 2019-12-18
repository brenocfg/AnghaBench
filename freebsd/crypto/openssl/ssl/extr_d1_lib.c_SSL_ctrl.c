#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_20__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_27__ {int version; int /*<<< orphan*/  rlayer; TYPE_3__* d1; int /*<<< orphan*/  msg_callback_arg; int /*<<< orphan*/  (* msg_callback ) (int,int,unsigned int,unsigned char*,int,TYPE_4__*,int /*<<< orphan*/ ) ;TYPE_2__* method; TYPE_1__* ctx; int /*<<< orphan*/ * handshake_func; } ;
struct TYPE_26__ {int handshake_read_seq; int handshake_write_seq; int next_handshake_write_seq; } ;
struct TYPE_25__ {scalar_t__ version; } ;
struct TYPE_24__ {unsigned char* buf; } ;
struct TYPE_23__ {scalar_t__ (* app_verify_cookie_cb ) (TYPE_4__*,unsigned char*,unsigned int) ;scalar_t__ (* app_gen_cookie_cb ) (TYPE_4__*,unsigned char*,unsigned int*) ;} ;
struct TYPE_22__ {unsigned char* buf; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  BIO_ADDR ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDR_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDR_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_ADDR_new () ; 
 scalar_t__ BIO_dgram_get_peer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_dgram_set_peer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_flush (int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,scalar_t__) ; 
 scalar_t__ BIO_should_retry (int /*<<< orphan*/ *) ; 
 int BIO_write (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int DTLS1_COOKIE_LENGTH ; 
 size_t DTLS1_HM_HEADER_LENGTH ; 
 unsigned int DTLS1_MT_HELLO_VERIFY_REQUEST ; 
 int DTLS1_RT_HEADER_LENGTH ; 
 int DTLS1_VERSION ; 
 unsigned int DTLS1_VERSION_MAJOR ; 
 scalar_t__ DTLS_ANY_VERSION ; 
 int /*<<< orphan*/  DTLS_RECORD_LAYER_set_write_sequence (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ DTLS_VERSION_LT (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int LISTEN_SEND_VERIFY_REQUEST ; 
 int LISTEN_SUCCESS ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,unsigned char*,int) ; 
 unsigned char* PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_net_3_len (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  PACKET_get_sub_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 TYPE_20__* RECORD_LAYER_get_rbuf (int /*<<< orphan*/ *) ; 
 TYPE_19__* RECORD_LAYER_get_wbuf (int /*<<< orphan*/ *) ; 
 int SEQ_NUM_SIZE ; 
 int SSL3_ALIGN_PAYLOAD ; 
 unsigned int SSL3_MT_CLIENT_HELLO ; 
 int SSL3_RANDOM_SIZE ; 
 unsigned int SSL3_RT_HANDSHAKE ; 
 unsigned int SSL3_RT_HEADER ; 
 size_t SSL3_RT_HEADER_LENGTH ; 
 scalar_t__ SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_F_DTLSV1_LISTEN ; 
 int /*<<< orphan*/  SSL_OP_COOKIE_EXCHANGE ; 
 int /*<<< orphan*/  SSL_R_BAD_PROTOCOL_VERSION_NUMBER ; 
 int /*<<< orphan*/  SSL_R_BIO_NOT_SET ; 
 int /*<<< orphan*/  SSL_R_COOKIE_GEN_CALLBACK_FAILURE ; 
 int /*<<< orphan*/  SSL_R_FRAGMENTED_CLIENT_HELLO ; 
 int /*<<< orphan*/  SSL_R_INVALID_SEQUENCE_NUMBER ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_NO_VERIFY_COOKIE_CALLBACK ; 
 int /*<<< orphan*/  SSL_R_RECORD_TOO_SMALL ; 
 int /*<<< orphan*/  SSL_R_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  SSL_R_UNSUPPORTED_SSL_VERSION ; 
 int /*<<< orphan*/  SSL_R_WRONG_VERSION_NUMBER ; 
 int /*<<< orphan*/  SSL_clear (TYPE_4__*) ; 
 int /*<<< orphan*/ * SSL_get_rbio (TYPE_4__*) ; 
 int /*<<< orphan*/ * SSL_get_wbio (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_set_accept_state (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_set_options (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_init_static_len (int /*<<< orphan*/ *,unsigned char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_sys_error () ; 
 int /*<<< orphan*/  dtls_buffer_listen_record (TYPE_4__*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  dtls_raw_hello_verify_request (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ossl_statem_set_hello_verify_done (TYPE_4__*) ; 
 int /*<<< orphan*/  ssl3_setup_buffers (TYPE_4__*) ; 
 scalar_t__ ssl_get_max_send_fragment (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int,int,unsigned int,unsigned char*,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int,unsigned int,unsigned char const*,size_t,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_4__*,unsigned char*,unsigned int) ; 
 scalar_t__ stub4 (TYPE_4__*,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  stub5 (int,int,unsigned int,unsigned char*,int,TYPE_4__*,int /*<<< orphan*/ ) ; 

int DTLSv1_listen(SSL *s, BIO_ADDR *client)
{
    int next, n, ret = 0;
    unsigned char cookie[DTLS1_COOKIE_LENGTH];
    unsigned char seq[SEQ_NUM_SIZE];
    const unsigned char *data;
    unsigned char *buf, *wbuf;
    size_t fragoff, fraglen, msglen, reclen, align = 0;
    unsigned int rectype, versmajor, msgseq, msgtype, clientvers, cookielen;
    BIO *rbio, *wbio;
    BIO_ADDR *tmpclient = NULL;
    PACKET pkt, msgpkt, msgpayload, session, cookiepkt;

    if (s->handshake_func == NULL) {
        /* Not properly initialized yet */
        SSL_set_accept_state(s);
    }

    /* Ensure there is no state left over from a previous invocation */
    if (!SSL_clear(s))
        return -1;

    ERR_clear_error();

    rbio = SSL_get_rbio(s);
    wbio = SSL_get_wbio(s);

    if (!rbio || !wbio) {
        SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_BIO_NOT_SET);
        return -1;
    }

    /*
     * Note: This check deliberately excludes DTLS1_BAD_VER because that version
     * requires the MAC to be calculated *including* the first ClientHello
     * (without the cookie). Since DTLSv1_listen is stateless that cannot be
     * supported. DTLS1_BAD_VER must use cookies in a stateful manner (e.g. via
     * SSL_accept)
     */
    if ((s->version & 0xff00) != (DTLS1_VERSION & 0xff00)) {
        SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_UNSUPPORTED_SSL_VERSION);
        return -1;
    }

    if (!ssl3_setup_buffers(s)) {
        /* SSLerr already called */
        return -1;
    }
    buf = RECORD_LAYER_get_rbuf(&s->rlayer)->buf;
    wbuf = RECORD_LAYER_get_wbuf(&s->rlayer)[0].buf;
#if defined(SSL3_ALIGN_PAYLOAD)
# if SSL3_ALIGN_PAYLOAD != 0
    /*
     * Using SSL3_RT_HEADER_LENGTH here instead of DTLS1_RT_HEADER_LENGTH for
     * consistency with ssl3_read_n. In practice it should make no difference
     * for sensible values of SSL3_ALIGN_PAYLOAD because the difference between
     * SSL3_RT_HEADER_LENGTH and DTLS1_RT_HEADER_LENGTH is exactly 8
     */
    align = (size_t)buf + SSL3_RT_HEADER_LENGTH;
    align = SSL3_ALIGN_PAYLOAD - 1 - ((align - 1) % SSL3_ALIGN_PAYLOAD);
# endif
#endif
    buf += align;

    do {
        /* Get a packet */

        clear_sys_error();
        n = BIO_read(rbio, buf, SSL3_RT_MAX_PLAIN_LENGTH
                                + DTLS1_RT_HEADER_LENGTH);
        if (n <= 0) {
            if (BIO_should_retry(rbio)) {
                /* Non-blocking IO */
                goto end;
            }
            return -1;
        }

        if (!PACKET_buf_init(&pkt, buf, n)) {
            SSLerr(SSL_F_DTLSV1_LISTEN, ERR_R_INTERNAL_ERROR);
            return -1;
        }

        /*
         * Parse the received record. If there are any problems with it we just
         * dump it - with no alert. RFC6347 says this "Unlike TLS, DTLS is
         * resilient in the face of invalid records (e.g., invalid formatting,
         * length, MAC, etc.).  In general, invalid records SHOULD be silently
         * discarded, thus preserving the association; however, an error MAY be
         * logged for diagnostic purposes."
         */

        /* this packet contained a partial record, dump it */
        if (n < DTLS1_RT_HEADER_LENGTH) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_RECORD_TOO_SMALL);
            goto end;
        }

        if (s->msg_callback)
            s->msg_callback(0, 0, SSL3_RT_HEADER, buf,
                            DTLS1_RT_HEADER_LENGTH, s, s->msg_callback_arg);

        /* Get the record header */
        if (!PACKET_get_1(&pkt, &rectype)
            || !PACKET_get_1(&pkt, &versmajor)) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_LENGTH_MISMATCH);
            goto end;
        }

        if (rectype != SSL3_RT_HANDSHAKE) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_UNEXPECTED_MESSAGE);
            goto end;
        }

        /*
         * Check record version number. We only check that the major version is
         * the same.
         */
        if (versmajor != DTLS1_VERSION_MAJOR) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_BAD_PROTOCOL_VERSION_NUMBER);
            goto end;
        }

        if (!PACKET_forward(&pkt, 1)
            /* Save the sequence number: 64 bits, with top 2 bytes = epoch */
            || !PACKET_copy_bytes(&pkt, seq, SEQ_NUM_SIZE)
            || !PACKET_get_length_prefixed_2(&pkt, &msgpkt)) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_LENGTH_MISMATCH);
            goto end;
        }
        reclen = PACKET_remaining(&msgpkt);
        /*
         * We allow data remaining at the end of the packet because there could
         * be a second record (but we ignore it)
         */

        /* This is an initial ClientHello so the epoch has to be 0 */
        if (seq[0] != 0 || seq[1] != 0) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_UNEXPECTED_MESSAGE);
            goto end;
        }

        /* Get a pointer to the raw message for the later callback */
        data = PACKET_data(&msgpkt);

        /* Finished processing the record header, now process the message */
        if (!PACKET_get_1(&msgpkt, &msgtype)
            || !PACKET_get_net_3_len(&msgpkt, &msglen)
            || !PACKET_get_net_2(&msgpkt, &msgseq)
            || !PACKET_get_net_3_len(&msgpkt, &fragoff)
            || !PACKET_get_net_3_len(&msgpkt, &fraglen)
            || !PACKET_get_sub_packet(&msgpkt, &msgpayload, fraglen)
            || PACKET_remaining(&msgpkt) != 0) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_LENGTH_MISMATCH);
            goto end;
        }

        if (msgtype != SSL3_MT_CLIENT_HELLO) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_UNEXPECTED_MESSAGE);
            goto end;
        }

        /* Message sequence number can only be 0 or 1 */
        if (msgseq > 2) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_INVALID_SEQUENCE_NUMBER);
            goto end;
        }

        /*
         * We don't support fragment reassembly for ClientHellos whilst
         * listening because that would require server side state (which is
         * against the whole point of the ClientHello/HelloVerifyRequest
         * mechanism). Instead we only look at the first ClientHello fragment
         * and require that the cookie must be contained within it.
         */
        if (fragoff != 0 || fraglen > msglen) {
            /* Non initial ClientHello fragment (or bad fragment) */
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_FRAGMENTED_CLIENT_HELLO);
            goto end;
        }

        if (s->msg_callback)
            s->msg_callback(0, s->version, SSL3_RT_HANDSHAKE, data,
                            fraglen + DTLS1_HM_HEADER_LENGTH, s,
                            s->msg_callback_arg);

        if (!PACKET_get_net_2(&msgpayload, &clientvers)) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_LENGTH_MISMATCH);
            goto end;
        }

        /*
         * Verify client version is supported
         */
        if (DTLS_VERSION_LT(clientvers, (unsigned int)s->method->version) &&
            s->method->version != DTLS_ANY_VERSION) {
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_WRONG_VERSION_NUMBER);
            goto end;
        }

        if (!PACKET_forward(&msgpayload, SSL3_RANDOM_SIZE)
            || !PACKET_get_length_prefixed_1(&msgpayload, &session)
            || !PACKET_get_length_prefixed_1(&msgpayload, &cookiepkt)) {
            /*
             * Could be malformed or the cookie does not fit within the initial
             * ClientHello fragment. Either way we can't handle it.
             */
            SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_LENGTH_MISMATCH);
            goto end;
        }

        /*
         * Check if we have a cookie or not. If not we need to send a
         * HelloVerifyRequest.
         */
        if (PACKET_remaining(&cookiepkt) == 0) {
            next = LISTEN_SEND_VERIFY_REQUEST;
        } else {
            /*
             * We have a cookie, so lets check it.
             */
            if (s->ctx->app_verify_cookie_cb == NULL) {
                SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_NO_VERIFY_COOKIE_CALLBACK);
                /* This is fatal */
                return -1;
            }
            if (s->ctx->app_verify_cookie_cb(s, PACKET_data(&cookiepkt),
                    (unsigned int)PACKET_remaining(&cookiepkt)) == 0) {
                /*
                 * We treat invalid cookies in the same was as no cookie as
                 * per RFC6347
                 */
                next = LISTEN_SEND_VERIFY_REQUEST;
            } else {
                /* Cookie verification succeeded */
                next = LISTEN_SUCCESS;
            }
        }

        if (next == LISTEN_SEND_VERIFY_REQUEST) {
            WPACKET wpkt;
            unsigned int version;
            size_t wreclen;

            /*
             * There was no cookie in the ClientHello so we need to send a
             * HelloVerifyRequest. If this fails we do not worry about trying
             * to resend, we just drop it.
             */

            /* Generate the cookie */
            if (s->ctx->app_gen_cookie_cb == NULL ||
                s->ctx->app_gen_cookie_cb(s, cookie, &cookielen) == 0 ||
                cookielen > 255) {
                SSLerr(SSL_F_DTLSV1_LISTEN, SSL_R_COOKIE_GEN_CALLBACK_FAILURE);
                /* This is fatal */
                return -1;
            }

            /*
             * Special case: for hello verify request, client version 1.0 and we
             * haven't decided which version to use yet send back using version
             * 1.0 header: otherwise some clients will ignore it.
             */
            version = (s->method->version == DTLS_ANY_VERSION) ? DTLS1_VERSION
                                                               : s->version;

            /* Construct the record and message headers */
            if (!WPACKET_init_static_len(&wpkt,
                                         wbuf,
                                         ssl_get_max_send_fragment(s)
                                         + DTLS1_RT_HEADER_LENGTH,
                                         0)
                    || !WPACKET_put_bytes_u8(&wpkt, SSL3_RT_HANDSHAKE)
                    || !WPACKET_put_bytes_u16(&wpkt, version)
                       /*
                        * Record sequence number is always the same as in the
                        * received ClientHello
                        */
                    || !WPACKET_memcpy(&wpkt, seq, SEQ_NUM_SIZE)
                       /* End of record, start sub packet for message */
                    || !WPACKET_start_sub_packet_u16(&wpkt)
                       /* Message type */
                    || !WPACKET_put_bytes_u8(&wpkt,
                                             DTLS1_MT_HELLO_VERIFY_REQUEST)
                       /*
                        * Message length - doesn't follow normal TLS convention:
                        * the length isn't the last thing in the message header.
                        * We'll need to fill this in later when we know the
                        * length. Set it to zero for now
                        */
                    || !WPACKET_put_bytes_u24(&wpkt, 0)
                       /*
                        * Message sequence number is always 0 for a
                        * HelloVerifyRequest
                        */
                    || !WPACKET_put_bytes_u16(&wpkt, 0)
                       /*
                        * We never fragment a HelloVerifyRequest, so fragment
                        * offset is 0
                        */
                    || !WPACKET_put_bytes_u24(&wpkt, 0)
                       /*
                        * Fragment length is the same as message length, but
                        * this *is* the last thing in the message header so we
                        * can just start a sub-packet. No need to come back
                        * later for this one.
                        */
                    || !WPACKET_start_sub_packet_u24(&wpkt)
                       /* Create the actual HelloVerifyRequest body */
                    || !dtls_raw_hello_verify_request(&wpkt, cookie, cookielen)
                       /* Close message body */
                    || !WPACKET_close(&wpkt)
                       /* Close record body */
                    || !WPACKET_close(&wpkt)
                    || !WPACKET_get_total_written(&wpkt, &wreclen)
                    || !WPACKET_finish(&wpkt)) {
                SSLerr(SSL_F_DTLSV1_LISTEN, ERR_R_INTERNAL_ERROR);
                WPACKET_cleanup(&wpkt);
                /* This is fatal */
                return -1;
            }

            /*
             * Fix up the message len in the message header. Its the same as the
             * fragment len which has been filled in by WPACKET, so just copy
             * that. Destination for the message len is after the record header
             * plus one byte for the message content type. The source is the
             * last 3 bytes of the message header
             */
            memcpy(&wbuf[DTLS1_RT_HEADER_LENGTH + 1],
                   &wbuf[DTLS1_RT_HEADER_LENGTH + DTLS1_HM_HEADER_LENGTH - 3],
                   3);

            if (s->msg_callback)
                s->msg_callback(1, 0, SSL3_RT_HEADER, buf,
                                DTLS1_RT_HEADER_LENGTH, s, s->msg_callback_arg);

            if ((tmpclient = BIO_ADDR_new()) == NULL) {
                SSLerr(SSL_F_DTLSV1_LISTEN, ERR_R_MALLOC_FAILURE);
                goto end;
            }

            /*
             * This is unnecessary if rbio and wbio are one and the same - but
             * maybe they're not. We ignore errors here - some BIOs do not
             * support this.
             */
            if (BIO_dgram_get_peer(rbio, tmpclient) > 0) {
                (void)BIO_dgram_set_peer(wbio, tmpclient);
            }
            BIO_ADDR_free(tmpclient);
            tmpclient = NULL;

            /* TODO(size_t): convert this call */
            if (BIO_write(wbio, wbuf, wreclen) < (int)wreclen) {
                if (BIO_should_retry(wbio)) {
                    /*
                     * Non-blocking IO...but we're stateless, so we're just
                     * going to drop this packet.
                     */
                    goto end;
                }
                return -1;
            }

            if (BIO_flush(wbio) <= 0) {
                if (BIO_should_retry(wbio)) {
                    /*
                     * Non-blocking IO...but we're stateless, so we're just
                     * going to drop this packet.
                     */
                    goto end;
                }
                return -1;
            }
        }
    } while (next != LISTEN_SUCCESS);

    /*
     * Set expected sequence numbers to continue the handshake.
     */
    s->d1->handshake_read_seq = 1;
    s->d1->handshake_write_seq = 1;
    s->d1->next_handshake_write_seq = 1;
    DTLS_RECORD_LAYER_set_write_sequence(&s->rlayer, seq);

    /*
     * We are doing cookie exchange, so make sure we set that option in the
     * SSL object
     */
    SSL_set_options(s, SSL_OP_COOKIE_EXCHANGE);

    /*
     * Tell the state machine that we've done the initial hello verify
     * exchange
     */
    ossl_statem_set_hello_verify_done(s);

    /*
     * Some BIOs may not support this. If we fail we clear the client address
     */
    if (BIO_dgram_get_peer(rbio, client) <= 0)
        BIO_ADDR_clear(client);

    /* Buffer the record in the processed_rcds queue */
    if (!dtls_buffer_listen_record(s, reclen, seq, align))
        return -1;

    ret = 1;
 end:
    BIO_ADDR_free(tmpclient);
    return ret;
}