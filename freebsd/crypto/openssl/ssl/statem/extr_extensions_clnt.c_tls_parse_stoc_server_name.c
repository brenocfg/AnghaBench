#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_9__ {int /*<<< orphan*/ * hostname; } ;
struct TYPE_10__ {TYPE_2__* session; TYPE_3__ ext; int /*<<< orphan*/  hit; } ;
struct TYPE_7__ {int /*<<< orphan*/ * hostname; } ;
struct TYPE_8__ {TYPE_1__ ext; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/ * OPENSSL_strdup (int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_SERVER_NAME ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_stoc_server_name(SSL *s, PACKET *pkt, unsigned int context,
                               X509 *x, size_t chainidx)
{
    if (s->ext.hostname == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_SERVER_NAME,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (PACKET_remaining(pkt) > 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_SERVER_NAME,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    if (!s->hit) {
        if (s->session->ext.hostname != NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_SERVER_NAME,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
        s->session->ext.hostname = OPENSSL_strdup(s->ext.hostname);
        if (s->session->ext.hostname == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_SERVER_NAME,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }

    return 1;
}