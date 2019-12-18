#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int sid_ctx_length; TYPE_2__* s3; int /*<<< orphan*/  version; TYPE_3__* session; int /*<<< orphan*/  sid_ctx; TYPE_1__* session_ctx; } ;
struct TYPE_15__ {scalar_t__ timeout; int sid_ctx_length; int /*<<< orphan*/  flags; int /*<<< orphan*/  verify_result; int /*<<< orphan*/  ssl_version; int /*<<< orphan*/  sid_ctx; scalar_t__ session_id_length; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {scalar_t__ session_timeout; } ;
typedef  TYPE_3__ SSL_SESSION ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL_GET_NEW_SESSION ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_3__*) ; 
 TYPE_3__* SSL_SESSION_new () ; 
 int /*<<< orphan*/  SSL_SESS_FLAG_EXTMS ; 
 scalar_t__ SSL_get_default_timeout (TYPE_4__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS1_FLAGS_RECEIVED_EXTMS ; 
 int /*<<< orphan*/  X509_V_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssl_generate_session_id (TYPE_4__*,TYPE_3__*) ; 

int ssl_get_new_session(SSL *s, int session)
{
    /* This gets used by clients and servers. */

    SSL_SESSION *ss = NULL;

    if ((ss = SSL_SESSION_new()) == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GET_NEW_SESSION,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }

    /* If the context has a default timeout, use it */
    if (s->session_ctx->session_timeout == 0)
        ss->timeout = SSL_get_default_timeout(s);
    else
        ss->timeout = s->session_ctx->session_timeout;

    SSL_SESSION_free(s->session);
    s->session = NULL;

    if (session) {
        if (SSL_IS_TLS13(s)) {
            /*
             * We generate the session id while constructing the
             * NewSessionTicket in TLSv1.3.
             */
            ss->session_id_length = 0;
        } else if (!ssl_generate_session_id(s, ss)) {
            /* SSLfatal() already called */
            SSL_SESSION_free(ss);
            return 0;
        }

    } else {
        ss->session_id_length = 0;
    }

    if (s->sid_ctx_length > sizeof(ss->sid_ctx)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GET_NEW_SESSION,
                 ERR_R_INTERNAL_ERROR);
        SSL_SESSION_free(ss);
        return 0;
    }
    memcpy(ss->sid_ctx, s->sid_ctx, s->sid_ctx_length);
    ss->sid_ctx_length = s->sid_ctx_length;
    s->session = ss;
    ss->ssl_version = s->version;
    ss->verify_result = X509_V_OK;

    /* If client supports extended master secret set it in session */
    if (s->s3->flags & TLS1_FLAGS_RECEIVED_EXTMS)
        ss->flags |= SSL_SESS_FLAG_EXTMS;

    return 1;
}