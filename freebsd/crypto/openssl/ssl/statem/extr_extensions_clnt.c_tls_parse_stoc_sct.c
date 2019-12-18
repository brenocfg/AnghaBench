#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_7__ {int /*<<< orphan*/ * scts; scalar_t__ scts_len; } ;
struct TYPE_9__ {TYPE_2__* cert; TYPE_1__ ext; int /*<<< orphan*/ * ct_validation_callback; } ;
struct TYPE_8__ {int /*<<< orphan*/  custext; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  ENDPOINT ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPOINT_BOTH ; 
 int /*<<< orphan*/  ENDPOINT_CLIENT ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 unsigned int SSL_EXT_TLS1_2_SERVER_HELLO ; 
 unsigned int SSL_EXT_TLS1_3_CERTIFICATE_REQUEST ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_SCT ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_AD_UNSUPPORTED_EXTENSION ; 
 int /*<<< orphan*/  TLSEXT_TYPE_signed_certificate_timestamp ; 
 int /*<<< orphan*/ * custom_ext_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  custom_ext_parse (TYPE_3__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t) ; 

int tls_parse_stoc_sct(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                       size_t chainidx)
{
    if (context == SSL_EXT_TLS1_3_CERTIFICATE_REQUEST) {
        /* We ignore this if the server sends it in a CertificateRequest */
        /* TODO(TLS1.3): Add support for this */
        return 1;
    }

    /*
     * Only take it if we asked for it - i.e if there is no CT validation
     * callback set, then a custom extension MAY be processing it, so we
     * need to let control continue to flow to that.
     */
    if (s->ct_validation_callback != NULL) {
        size_t size = PACKET_remaining(pkt);

        /* Simply copy it off for later processing */
        OPENSSL_free(s->ext.scts);
        s->ext.scts = NULL;

        s->ext.scts_len = (uint16_t)size;
        if (size > 0) {
            s->ext.scts = OPENSSL_malloc(size);
            if (s->ext.scts == NULL
                    || !PACKET_copy_bytes(pkt, s->ext.scts, size)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_SCT,
                         ERR_R_INTERNAL_ERROR);
                return 0;
            }
        }
    } else {
        ENDPOINT role = (context & SSL_EXT_TLS1_2_SERVER_HELLO) != 0
                        ? ENDPOINT_CLIENT : ENDPOINT_BOTH;

        /*
         * If we didn't ask for it then there must be a custom extension,
         * otherwise this is unsolicited.
         */
        if (custom_ext_find(&s->cert->custext, role,
                            TLSEXT_TYPE_signed_certificate_timestamp,
                            NULL) == NULL) {
            SSLfatal(s, TLS1_AD_UNSUPPORTED_EXTENSION, SSL_F_TLS_PARSE_STOC_SCT,
                     SSL_R_BAD_EXTENSION);
            return 0;
        }

        if (!custom_ext_parse(s, context,
                             TLSEXT_TYPE_signed_certificate_timestamp,
                             PACKET_data(pkt), PACKET_remaining(pkt),
                             x, chainidx)) {
            /* SSLfatal already called */
            return 0;
        }
    }

    return 1;
}