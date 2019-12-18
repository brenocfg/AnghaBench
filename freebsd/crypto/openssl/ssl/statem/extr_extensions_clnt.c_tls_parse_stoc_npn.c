#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_13__ {unsigned char npn_len; int /*<<< orphan*/ * npn; } ;
struct TYPE_15__ {TYPE_4__* s3; TYPE_3__ ext; TYPE_2__* ctx; } ;
struct TYPE_14__ {int npn_seen; } ;
struct TYPE_11__ {scalar_t__ (* npn_select_cb ) (TYPE_5__*,unsigned char**,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  npn_select_cb_arg; } ;
struct TYPE_12__ {TYPE_1__ ext; } ;
typedef  TYPE_5__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (unsigned char) ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_UNSUPPORTED_EXTENSION ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_NPN ; 
 int /*<<< orphan*/  SSL_IS_FIRST_HANDSHAKE (TYPE_5__*) ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 scalar_t__ SSL_TLSEXT_ERR_OK ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,unsigned char) ; 
 int /*<<< orphan*/  ssl_next_proto_validate (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_5__*,unsigned char**,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_stoc_npn(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                       size_t chainidx)
{
    unsigned char *selected;
    unsigned char selected_len;
    PACKET tmppkt;

    /* Check if we are in a renegotiation. If so ignore this extension */
    if (!SSL_IS_FIRST_HANDSHAKE(s))
        return 1;

    /* We must have requested it. */
    if (s->ctx->ext.npn_select_cb == NULL) {
        SSLfatal(s, SSL_AD_UNSUPPORTED_EXTENSION, SSL_F_TLS_PARSE_STOC_NPN,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    /* The data must be valid */
    tmppkt = *pkt;
    if (!ssl_next_proto_validate(s, &tmppkt)) {
        /* SSLfatal() already called */
        return 0;
    }
    if (s->ctx->ext.npn_select_cb(s, &selected, &selected_len,
                                  PACKET_data(pkt),
                                  PACKET_remaining(pkt),
                                  s->ctx->ext.npn_select_cb_arg) !=
             SSL_TLSEXT_ERR_OK) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS_PARSE_STOC_NPN,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    /*
     * Could be non-NULL if server has sent multiple NPN extensions in
     * a single Serverhello
     */
    OPENSSL_free(s->ext.npn);
    s->ext.npn = OPENSSL_malloc(selected_len);
    if (s->ext.npn == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_NPN,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    memcpy(s->ext.npn, selected, selected_len);
    s->ext.npn_len = selected_len;
    s->s3->npn_seen = 1;

    return 1;
}