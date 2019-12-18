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
struct TYPE_9__ {int /*<<< orphan*/  early_data; int /*<<< orphan*/  early_data_ok; } ;
struct TYPE_10__ {TYPE_3__ ext; int /*<<< orphan*/  hit; TYPE_2__* session; } ;
struct TYPE_7__ {unsigned long max_early_data; } ;
struct TYPE_8__ {TYPE_1__ ext; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_get_net_4 (int /*<<< orphan*/ *,unsigned long*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_ACCEPTED ; 
 unsigned int SSL_EXT_TLS1_3_NEW_SESSION_TICKET ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_EARLY_DATA ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSL_R_INVALID_MAX_EARLY_DATA ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_stoc_early_data(SSL *s, PACKET *pkt, unsigned int context,
                              X509 *x, size_t chainidx)
{
    if (context == SSL_EXT_TLS1_3_NEW_SESSION_TICKET) {
        unsigned long max_early_data;

        if (!PACKET_get_net_4(pkt, &max_early_data)
                || PACKET_remaining(pkt) != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_EARLY_DATA,
                     SSL_R_INVALID_MAX_EARLY_DATA);
            return 0;
        }

        s->session->ext.max_early_data = max_early_data;

        return 1;
    }

    if (PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_EARLY_DATA,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    if (!s->ext.early_data_ok
            || !s->hit) {
        /*
         * If we get here then we didn't send early data, or we didn't resume
         * using the first identity, or the SNI/ALPN is not consistent so the
         * server should not be accepting it.
         */
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_STOC_EARLY_DATA,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    s->ext.early_data = SSL_EARLY_DATA_ACCEPTED;

    return 1;
}