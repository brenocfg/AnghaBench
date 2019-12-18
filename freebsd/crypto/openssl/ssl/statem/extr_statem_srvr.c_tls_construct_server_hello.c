#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_20__ {scalar_t__ hello_retry_request; int version; size_t tmp_session_id_len; unsigned char* tmp_session_id; int verify_mode; scalar_t__ hit; TYPE_12__* session; TYPE_5__* s3; TYPE_3__* method; TYPE_1__* ctx; } ;
struct TYPE_18__ {int /*<<< orphan*/  new_cipher; TYPE_2__* new_compression; } ;
struct TYPE_19__ {TYPE_4__ tmp; int /*<<< orphan*/  server_random; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* put_cipher_by_char ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ;} ;
struct TYPE_16__ {int id; } ;
struct TYPE_15__ {int session_cache_mode; } ;
struct TYPE_14__ {size_t session_id_length; unsigned char* session_id; scalar_t__ not_resumable; } ;
typedef  TYPE_6__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_EXT_TLS1_2_SERVER_HELLO ; 
 int /*<<< orphan*/  SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST ; 
 int /*<<< orphan*/  SSL_EXT_TLS1_3_SERVER_HELLO ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_SERVER_HELLO ; 
 scalar_t__ SSL_HRR_PENDING ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_6__*) ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_12__*) ; 
 int SSL_SESS_CACHE_SERVER ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSLfatal (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS1_2_VERSION ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  create_synthetic_message_hash (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrrrandom ; 
 int /*<<< orphan*/  ssl3_digest_cached_records (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  tls_construct_extensions (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int tls_construct_server_hello(SSL *s, WPACKET *pkt)
{
    int compm;
    size_t sl, len;
    int version;
    unsigned char *session_id;
    int usetls13 = SSL_IS_TLS13(s) || s->hello_retry_request == SSL_HRR_PENDING;

    version = usetls13 ? TLS1_2_VERSION : s->version;
    if (!WPACKET_put_bytes_u16(pkt, version)
               /*
                * Random stuff. Filling of the server_random takes place in
                * tls_process_client_hello()
                */
            || !WPACKET_memcpy(pkt,
                               s->hello_retry_request == SSL_HRR_PENDING
                                   ? hrrrandom : s->s3->server_random,
                               SSL3_RANDOM_SIZE)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_SERVER_HELLO,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /*-
     * There are several cases for the session ID to send
     * back in the server hello:
     * - For session reuse from the session cache,
     *   we send back the old session ID.
     * - If stateless session reuse (using a session ticket)
     *   is successful, we send back the client's "session ID"
     *   (which doesn't actually identify the session).
     * - If it is a new session, we send back the new
     *   session ID.
     * - However, if we want the new session to be single-use,
     *   we send back a 0-length session ID.
     * - In TLSv1.3 we echo back the session id sent to us by the client
     *   regardless
     * s->hit is non-zero in either case of session reuse,
     * so the following won't overwrite an ID that we're supposed
     * to send back.
     */
    if (s->session->not_resumable ||
        (!(s->ctx->session_cache_mode & SSL_SESS_CACHE_SERVER)
         && !s->hit))
        s->session->session_id_length = 0;

    if (usetls13) {
        sl = s->tmp_session_id_len;
        session_id = s->tmp_session_id;
    } else {
        sl = s->session->session_id_length;
        session_id = s->session->session_id;
    }

    if (sl > sizeof(s->session->session_id)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_SERVER_HELLO,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /* set up the compression method */
#ifdef OPENSSL_NO_COMP
    compm = 0;
#else
    if (usetls13 || s->s3->tmp.new_compression == NULL)
        compm = 0;
    else
        compm = s->s3->tmp.new_compression->id;
#endif

    if (!WPACKET_sub_memcpy_u8(pkt, session_id, sl)
            || !s->method->put_cipher_by_char(s->s3->tmp.new_cipher, pkt, &len)
            || !WPACKET_put_bytes_u8(pkt, compm)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_SERVER_HELLO,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (!tls_construct_extensions(s, pkt,
                                  s->hello_retry_request == SSL_HRR_PENDING
                                      ? SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST
                                      : (SSL_IS_TLS13(s)
                                          ? SSL_EXT_TLS1_3_SERVER_HELLO
                                          : SSL_EXT_TLS1_2_SERVER_HELLO),
                                  NULL, 0)) {
        /* SSLfatal() already called */
        return 0;
    }

    if (s->hello_retry_request == SSL_HRR_PENDING) {
        /* Ditch the session. We'll create a new one next time around */
        SSL_SESSION_free(s->session);
        s->session = NULL;
        s->hit = 0;

        /*
         * Re-initialise the Transcript Hash. We're going to prepopulate it with
         * a synthetic message_hash in place of ClientHello1.
         */
        if (!create_synthetic_message_hash(s, NULL, 0, NULL, 0)) {
            /* SSLfatal() already called */
            return 0;
        }
    } else if (!(s->verify_mode & SSL_VERIFY_PEER)
                && !ssl3_digest_cached_records(s, 0)) {
        /* SSLfatal() already called */;
        return 0;
    }

    return 1;
}