#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {int /*<<< orphan*/ * exts; int /*<<< orphan*/ * ids; } ;
struct TYPE_7__ {scalar_t__ status_type; TYPE_1__ ocsp; } ;
struct TYPE_8__ {TYPE_2__ ext; scalar_t__ hit; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  OCSP_RESPID ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OCSP_RESPID_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* PACKET_data (int /*<<< orphan*/ *) ; 
 unsigned char const* PACKET_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLSEXT_STATUSTYPE_nothing ; 
 scalar_t__ TLSEXT_STATUSTYPE_ocsp ; 
 int /*<<< orphan*/  X509_EXTENSION_free ; 
 int /*<<< orphan*/ * d2i_OCSP_RESPID (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 int /*<<< orphan*/ * d2i_X509_EXTENSIONS (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 int /*<<< orphan*/ * sk_OCSP_RESPID_new_null () ; 
 int /*<<< orphan*/  sk_OCSP_RESPID_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  sk_OCSP_RESPID_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int tls_parse_ctos_status_request(SSL *s, PACKET *pkt, unsigned int context,
                                  X509 *x, size_t chainidx)
{
    PACKET responder_id_list, exts;

    /* We ignore this in a resumption handshake */
    if (s->hit)
        return 1;

    /* Not defined if we get one of these in a client Certificate */
    if (x != NULL)
        return 1;

    if (!PACKET_get_1(pkt, (unsigned int *)&s->ext.status_type)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, SSL_R_BAD_EXTENSION);
        return 0;
    }

    if (s->ext.status_type != TLSEXT_STATUSTYPE_ocsp) {
        /*
         * We don't know what to do with any other type so ignore it.
         */
        s->ext.status_type = TLSEXT_STATUSTYPE_nothing;
        return 1;
    }

    if (!PACKET_get_length_prefixed_2 (pkt, &responder_id_list)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, SSL_R_BAD_EXTENSION);
        return 0;
    }

    /*
     * We remove any OCSP_RESPIDs from a previous handshake
     * to prevent unbounded memory growth - CVE-2016-6304
     */
    sk_OCSP_RESPID_pop_free(s->ext.ocsp.ids, OCSP_RESPID_free);
    if (PACKET_remaining(&responder_id_list) > 0) {
        s->ext.ocsp.ids = sk_OCSP_RESPID_new_null();
        if (s->ext.ocsp.ids == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    } else {
        s->ext.ocsp.ids = NULL;
    }

    while (PACKET_remaining(&responder_id_list) > 0) {
        OCSP_RESPID *id;
        PACKET responder_id;
        const unsigned char *id_data;

        if (!PACKET_get_length_prefixed_2(&responder_id_list, &responder_id)
                || PACKET_remaining(&responder_id) == 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, SSL_R_BAD_EXTENSION);
            return 0;
        }

        id_data = PACKET_data(&responder_id);
        /* TODO(size_t): Convert d2i_* to size_t */
        id = d2i_OCSP_RESPID(NULL, &id_data,
                             (int)PACKET_remaining(&responder_id));
        if (id == NULL) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, SSL_R_BAD_EXTENSION);
            return 0;
        }

        if (id_data != PACKET_end(&responder_id)) {
            OCSP_RESPID_free(id);
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, SSL_R_BAD_EXTENSION);

            return 0;
        }

        if (!sk_OCSP_RESPID_push(s->ext.ocsp.ids, id)) {
            OCSP_RESPID_free(id);
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, ERR_R_INTERNAL_ERROR);

            return 0;
        }
    }

    /* Read in request_extensions */
    if (!PACKET_as_length_prefixed_2(pkt, &exts)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, SSL_R_BAD_EXTENSION);
        return 0;
    }

    if (PACKET_remaining(&exts) > 0) {
        const unsigned char *ext_data = PACKET_data(&exts);

        sk_X509_EXTENSION_pop_free(s->ext.ocsp.exts,
                                   X509_EXTENSION_free);
        s->ext.ocsp.exts =
            d2i_X509_EXTENSIONS(NULL, &ext_data, (int)PACKET_remaining(&exts));
        if (s->ext.ocsp.exts == NULL || ext_data != PACKET_end(&exts)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PARSE_CTOS_STATUS_REQUEST, SSL_R_BAD_EXTENSION);
            return 0;
        }
    }

    return 1;
}