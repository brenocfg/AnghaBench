#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {unsigned int legacy_version; unsigned int session_id_len; scalar_t__ dtls_cookie_len; scalar_t__ compressions_len; struct TYPE_17__* pre_proc_exts; int /*<<< orphan*/  pre_proc_exts_len; int /*<<< orphan*/  extensions; scalar_t__ compressions; int /*<<< orphan*/  ciphersuites; scalar_t__ dtls_cookie; scalar_t__ session_id; scalar_t__ random; scalar_t__ isv2; } ;
struct TYPE_16__ {int renegotiate; int options; int new_session; scalar_t__ hello_retry_request; TYPE_3__* clienthello; int /*<<< orphan*/  rlayer; TYPE_1__* s3; } ;
struct TYPE_15__ {int /*<<< orphan*/  send_connection_binding; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;
typedef  TYPE_3__ CLIENTHELLO_MSG ;

/* Variables and functions */
 unsigned int DTLS1_COOKIE_LENGTH ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 unsigned int MAX_COMPRESSIONS_SIZE ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_PROCESSING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_FINISHED_READING ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_3__*) ; 
 TYPE_3__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  PACKET_copy_all (int /*<<< orphan*/ *,scalar_t__,unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_sub_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  PACKET_null_init (int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ RECORD_LAYER_is_sslv2_record (int /*<<< orphan*/ *) ; 
 unsigned int SSL2_MT_CLIENT_HELLO ; 
 int /*<<< orphan*/  SSL3_AL_WARNING ; 
 unsigned int SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_NO_RENEGOTIATION ; 
 int /*<<< orphan*/  SSL_AD_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  SSL_EXT_CLIENT_HELLO ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CLIENT_HELLO ; 
 scalar_t__ SSL_HRR_NONE ; 
 scalar_t__ SSL_IS_DTLS (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_IS_FIRST_HANDSHAKE (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_IS_TLS13 (TYPE_2__*) ; 
 unsigned int SSL_MAX_SSL_SESSION_ID_LENGTH ; 
 int SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION ; 
 int SSL_OP_COOKIE_EXCHANGE ; 
 int SSL_OP_NO_RENEGOTIATION ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_LENGTH_TOO_SHORT ; 
 int /*<<< orphan*/  SSL_R_RECORD_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_UNEXPECTED_MESSAGE ; 
 int SSL_get_options (TYPE_2__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  ssl3_send_alert (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_collect_extensions (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ *,int) ; 

MSG_PROCESS_RETURN tls_process_client_hello(SSL *s, PACKET *pkt)
{
    /* |cookie| will only be initialized for DTLS. */
    PACKET session_id, compression, extensions, cookie;
    static const unsigned char null_compression = 0;
    CLIENTHELLO_MSG *clienthello = NULL;

    /* Check if this is actually an unexpected renegotiation ClientHello */
    if (s->renegotiate == 0 && !SSL_IS_FIRST_HANDSHAKE(s)) {
        if (!ossl_assert(!SSL_IS_TLS13(s))) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        if ((s->options & SSL_OP_NO_RENEGOTIATION) != 0
                || (!s->s3->send_connection_binding
                    && (s->options
                        & SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION) == 0)) {
            ssl3_send_alert(s, SSL3_AL_WARNING, SSL_AD_NO_RENEGOTIATION);
            return MSG_PROCESS_FINISHED_READING;
        }
        s->renegotiate = 1;
        s->new_session = 1;
    }

    clienthello = OPENSSL_zalloc(sizeof(*clienthello));
    if (clienthello == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    /*
     * First, parse the raw ClientHello data into the CLIENTHELLO_MSG structure.
     */
    clienthello->isv2 = RECORD_LAYER_is_sslv2_record(&s->rlayer);
    PACKET_null_init(&cookie);

    if (clienthello->isv2) {
        unsigned int mt;

        if (!SSL_IS_FIRST_HANDSHAKE(s)
                || s->hello_retry_request != SSL_HRR_NONE) {
            SSLfatal(s, SSL_AD_UNEXPECTED_MESSAGE,
                     SSL_F_TLS_PROCESS_CLIENT_HELLO, SSL_R_UNEXPECTED_MESSAGE);
            goto err;
        }

        /*-
         * An SSLv3/TLSv1 backwards-compatible CLIENT-HELLO in an SSLv2
         * header is sent directly on the wire, not wrapped as a TLS
         * record. Our record layer just processes the message length and passes
         * the rest right through. Its format is:
         * Byte  Content
         * 0-1   msg_length - decoded by the record layer
         * 2     msg_type - s->init_msg points here
         * 3-4   version
         * 5-6   cipher_spec_length
         * 7-8   session_id_length
         * 9-10  challenge_length
         * ...   ...
         */

        if (!PACKET_get_1(pkt, &mt)
            || mt != SSL2_MT_CLIENT_HELLO) {
            /*
             * Should never happen. We should have tested this in the record
             * layer in order to have determined that this is a SSLv2 record
             * in the first place
             */
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
    }

    if (!PACKET_get_net_2(pkt, &clienthello->legacy_version)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                 SSL_R_LENGTH_TOO_SHORT);
        goto err;
    }

    /* Parse the message and load client random. */
    if (clienthello->isv2) {
        /*
         * Handle an SSLv2 backwards compatible ClientHello
         * Note, this is only for SSLv3+ using the backward compatible format.
         * Real SSLv2 is not supported, and is rejected below.
         */
        unsigned int ciphersuite_len, session_id_len, challenge_len;
        PACKET challenge;

        if (!PACKET_get_net_2(pkt, &ciphersuite_len)
            || !PACKET_get_net_2(pkt, &session_id_len)
            || !PACKET_get_net_2(pkt, &challenge_len)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                     SSL_R_RECORD_LENGTH_MISMATCH);
            goto err;
        }

        if (session_id_len > SSL_MAX_SSL_SESSION_ID_LENGTH) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                     SSL_F_TLS_PROCESS_CLIENT_HELLO, SSL_R_LENGTH_MISMATCH);
            goto err;
        }

        if (!PACKET_get_sub_packet(pkt, &clienthello->ciphersuites,
                                   ciphersuite_len)
            || !PACKET_copy_bytes(pkt, clienthello->session_id, session_id_len)
            || !PACKET_get_sub_packet(pkt, &challenge, challenge_len)
            /* No extensions. */
            || PACKET_remaining(pkt) != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                     SSL_R_RECORD_LENGTH_MISMATCH);
            goto err;
        }
        clienthello->session_id_len = session_id_len;

        /* Load the client random and compression list. We use SSL3_RANDOM_SIZE
         * here rather than sizeof(clienthello->random) because that is the limit
         * for SSLv3 and it is fixed. It won't change even if
         * sizeof(clienthello->random) does.
         */
        challenge_len = challenge_len > SSL3_RANDOM_SIZE
                        ? SSL3_RANDOM_SIZE : challenge_len;
        memset(clienthello->random, 0, SSL3_RANDOM_SIZE);
        if (!PACKET_copy_bytes(&challenge,
                               clienthello->random + SSL3_RANDOM_SIZE -
                               challenge_len, challenge_len)
            /* Advertise only null compression. */
            || !PACKET_buf_init(&compression, &null_compression, 1)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        PACKET_null_init(&clienthello->extensions);
    } else {
        /* Regular ClientHello. */
        if (!PACKET_copy_bytes(pkt, clienthello->random, SSL3_RANDOM_SIZE)
            || !PACKET_get_length_prefixed_1(pkt, &session_id)
            || !PACKET_copy_all(&session_id, clienthello->session_id,
                    SSL_MAX_SSL_SESSION_ID_LENGTH,
                    &clienthello->session_id_len)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                     SSL_R_LENGTH_MISMATCH);
            goto err;
        }

        if (SSL_IS_DTLS(s)) {
            if (!PACKET_get_length_prefixed_1(pkt, &cookie)) {
                SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                         SSL_R_LENGTH_MISMATCH);
                goto err;
            }
            if (!PACKET_copy_all(&cookie, clienthello->dtls_cookie,
                                 DTLS1_COOKIE_LENGTH,
                                 &clienthello->dtls_cookie_len)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_PROCESS_CLIENT_HELLO, ERR_R_INTERNAL_ERROR);
                goto err;
            }
            /*
             * If we require cookies and this ClientHello doesn't contain one,
             * just return since we do not want to allocate any memory yet.
             * So check cookie length...
             */
            if (SSL_get_options(s) & SSL_OP_COOKIE_EXCHANGE) {
                if (clienthello->dtls_cookie_len == 0) {
                    OPENSSL_free(clienthello);
                    return MSG_PROCESS_FINISHED_READING;
                }
            }
        }

        if (!PACKET_get_length_prefixed_2(pkt, &clienthello->ciphersuites)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                     SSL_R_LENGTH_MISMATCH);
            goto err;
        }

        if (!PACKET_get_length_prefixed_1(pkt, &compression)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                     SSL_R_LENGTH_MISMATCH);
            goto err;
        }

        /* Could be empty. */
        if (PACKET_remaining(pkt) == 0) {
            PACKET_null_init(&clienthello->extensions);
        } else {
            if (!PACKET_get_length_prefixed_2(pkt, &clienthello->extensions)
                    || PACKET_remaining(pkt) != 0) {
                SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                         SSL_R_LENGTH_MISMATCH);
                goto err;
            }
        }
    }

    if (!PACKET_copy_all(&compression, clienthello->compressions,
                         MAX_COMPRESSIONS_SIZE,
                         &clienthello->compressions_len)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CLIENT_HELLO,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    /* Preserve the raw extensions PACKET for later use */
    extensions = clienthello->extensions;
    if (!tls_collect_extensions(s, &extensions, SSL_EXT_CLIENT_HELLO,
                                &clienthello->pre_proc_exts,
                                &clienthello->pre_proc_exts_len, 1)) {
        /* SSLfatal already been called */
        goto err;
    }
    s->clienthello = clienthello;

    return MSG_PROCESS_CONTINUE_PROCESSING;

 err:
    if (clienthello != NULL)
        OPENSSL_free(clienthello->pre_proc_exts);
    OPENSSL_free(clienthello);

    return MSG_PROCESS_ERROR;
}