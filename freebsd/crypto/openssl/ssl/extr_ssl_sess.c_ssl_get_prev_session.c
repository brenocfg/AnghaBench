#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_18__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  session_id_len; int /*<<< orphan*/  session_id; int /*<<< orphan*/  pre_proc_exts; } ;
struct TYPE_23__ {int ticket_expected; } ;
struct TYPE_25__ {scalar_t__ version; scalar_t__ sid_ctx_length; int verify_mode; TYPE_3__ ext; TYPE_4__* session; int /*<<< orphan*/  verify_result; TYPE_18__* session_ctx; TYPE_1__* s3; int /*<<< orphan*/  sid_ctx; } ;
struct TYPE_24__ {scalar_t__ ssl_version; scalar_t__ sid_ctx_length; long timeout; int flags; int /*<<< orphan*/  verify_result; scalar_t__ time; int /*<<< orphan*/  sid_ctx; } ;
struct TYPE_22__ {int /*<<< orphan*/  sess_hit; int /*<<< orphan*/  sess_timeout; } ;
struct TYPE_21__ {int flags; } ;
struct TYPE_20__ {TYPE_2__ stats; } ;
typedef  int SSL_TICKET_STATUS ;
typedef  TYPE_4__ SSL_SESSION ;
typedef  TYPE_5__ SSL ;
typedef  TYPE_6__ CLIENTHELLO_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_CTX_remove_session (TYPE_18__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_EXT_CLIENT_HELLO ; 
 int /*<<< orphan*/  SSL_F_SSL_GET_PREV_SESSION ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_5__*) ; 
 int /*<<< orphan*/  SSL_R_INCONSISTENT_EXTMS ; 
 int /*<<< orphan*/  SSL_R_SESSION_ID_CONTEXT_UNINITIALIZED ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_4__*) ; 
 int SSL_SESS_FLAG_EXTMS ; 
#define  SSL_TICKET_EMPTY 134 
#define  SSL_TICKET_FATAL_ERR_MALLOC 133 
#define  SSL_TICKET_FATAL_ERR_OTHER 132 
#define  SSL_TICKET_NONE 131 
#define  SSL_TICKET_NO_DECRYPT 130 
#define  SSL_TICKET_SUCCESS 129 
#define  SSL_TICKET_SUCCESS_RENEW 128 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS1_FLAGS_RECEIVED_EXTMS ; 
 int /*<<< orphan*/  TLSEXT_IDX_psk ; 
 int /*<<< orphan*/  TLSEXT_IDX_psk_kex_modes ; 
 TYPE_4__* lookup_sess_in_cache (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int tls_get_ticket_from_client (TYPE_5__*,TYPE_6__*,TYPE_4__**) ; 
 int /*<<< orphan*/  tls_parse_extension (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsan_counter (int /*<<< orphan*/ *) ; 

int ssl_get_prev_session(SSL *s, CLIENTHELLO_MSG *hello)
{
    /* This is used only by servers. */

    SSL_SESSION *ret = NULL;
    int fatal = 0;
    int try_session_cache = 0;
    SSL_TICKET_STATUS r;

    if (SSL_IS_TLS13(s)) {
        /*
         * By default we will send a new ticket. This can be overridden in the
         * ticket processing.
         */
        s->ext.ticket_expected = 1;
        if (!tls_parse_extension(s, TLSEXT_IDX_psk_kex_modes,
                                 SSL_EXT_CLIENT_HELLO, hello->pre_proc_exts,
                                 NULL, 0)
                || !tls_parse_extension(s, TLSEXT_IDX_psk, SSL_EXT_CLIENT_HELLO,
                                        hello->pre_proc_exts, NULL, 0))
            return -1;

        ret = s->session;
    } else {
        /* sets s->ext.ticket_expected */
        r = tls_get_ticket_from_client(s, hello, &ret);
        switch (r) {
        case SSL_TICKET_FATAL_ERR_MALLOC:
        case SSL_TICKET_FATAL_ERR_OTHER:
            fatal = 1;
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GET_PREV_SESSION,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        case SSL_TICKET_NONE:
        case SSL_TICKET_EMPTY:
            if (hello->session_id_len > 0) {
                try_session_cache = 1;
                ret = lookup_sess_in_cache(s, hello->session_id,
                                           hello->session_id_len);
            }
            break;
        case SSL_TICKET_NO_DECRYPT:
        case SSL_TICKET_SUCCESS:
        case SSL_TICKET_SUCCESS_RENEW:
            break;
        }
    }

    if (ret == NULL)
        goto err;

    /* Now ret is non-NULL and we own one of its reference counts. */

    /* Check TLS version consistency */
    if (ret->ssl_version != s->version)
        goto err;

    if (ret->sid_ctx_length != s->sid_ctx_length
        || memcmp(ret->sid_ctx, s->sid_ctx, ret->sid_ctx_length)) {
        /*
         * We have the session requested by the client, but we don't want to
         * use it in this context.
         */
        goto err;               /* treat like cache miss */
    }

    if ((s->verify_mode & SSL_VERIFY_PEER) && s->sid_ctx_length == 0) {
        /*
         * We can't be sure if this session is being used out of context,
         * which is especially important for SSL_VERIFY_PEER. The application
         * should have used SSL[_CTX]_set_session_id_context. For this error
         * case, we generate an error instead of treating the event like a
         * cache miss (otherwise it would be easy for applications to
         * effectively disable the session cache by accident without anyone
         * noticing).
         */

        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GET_PREV_SESSION,
                 SSL_R_SESSION_ID_CONTEXT_UNINITIALIZED);
        fatal = 1;
        goto err;
    }

    if (ret->timeout < (long)(time(NULL) - ret->time)) { /* timeout */
        tsan_counter(&s->session_ctx->stats.sess_timeout);
        if (try_session_cache) {
            /* session was from the cache, so remove it */
            SSL_CTX_remove_session(s->session_ctx, ret);
        }
        goto err;
    }

    /* Check extended master secret extension consistency */
    if (ret->flags & SSL_SESS_FLAG_EXTMS) {
        /* If old session includes extms, but new does not: abort handshake */
        if (!(s->s3->flags & TLS1_FLAGS_RECEIVED_EXTMS)) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_SSL_GET_PREV_SESSION,
                     SSL_R_INCONSISTENT_EXTMS);
            fatal = 1;
            goto err;
        }
    } else if (s->s3->flags & TLS1_FLAGS_RECEIVED_EXTMS) {
        /* If new session includes extms, but old does not: do not resume */
        goto err;
    }

    if (!SSL_IS_TLS13(s)) {
        /* We already did this for TLS1.3 */
        SSL_SESSION_free(s->session);
        s->session = ret;
    }

    tsan_counter(&s->session_ctx->stats.sess_hit);
    s->verify_result = s->session->verify_result;
    return 1;

 err:
    if (ret != NULL) {
        SSL_SESSION_free(ret);
        /* In TLSv1.3 s->session was already set to ret, so we NULL it out */
        if (SSL_IS_TLS13(s))
            s->session = NULL;

        if (!try_session_cache) {
            /*
             * The session was from a ticket, so we should issue a ticket for
             * the new session
             */
            s->ext.ticket_expected = 1;
        }
    }
    if (fatal)
        return -1;

    return 0;
}