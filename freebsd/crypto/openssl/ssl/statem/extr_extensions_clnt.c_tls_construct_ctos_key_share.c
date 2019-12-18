#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_9__ {TYPE_1__* s3; } ;
struct TYPE_8__ {scalar_t__ group_id; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_KEY_SHARE ; 
 int /*<<< orphan*/  SSL_R_NO_SUITABLE_KEY_SHARE ; 
 int /*<<< orphan*/  SSL_SECOP_CURVE_SUPPORTED ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_key_share ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_key_share (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tls1_get_supported_groups (TYPE_2__*,scalar_t__ const**,size_t*) ; 
 int /*<<< orphan*/  tls_curve_allowed (TYPE_2__*,scalar_t__ const,int /*<<< orphan*/ ) ; 

EXT_RETURN tls_construct_ctos_key_share(SSL *s, WPACKET *pkt,
                                        unsigned int context, X509 *x,
                                        size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    size_t i, num_groups = 0;
    const uint16_t *pgroups = NULL;
    uint16_t curve_id = 0;

    /* key_share extension */
    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_key_share)
               /* Extension data sub-packet */
            || !WPACKET_start_sub_packet_u16(pkt)
               /* KeyShare list sub-packet */
            || !WPACKET_start_sub_packet_u16(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_KEY_SHARE,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    tls1_get_supported_groups(s, &pgroups, &num_groups);

    /*
     * TODO(TLS1.3): Make the number of key_shares sent configurable. For
     * now, just send one
     */
    if (s->s3->group_id != 0) {
        curve_id = s->s3->group_id;
    } else {
        for (i = 0; i < num_groups; i++) {

            if (!tls_curve_allowed(s, pgroups[i], SSL_SECOP_CURVE_SUPPORTED))
                continue;

            curve_id = pgroups[i];
            break;
        }
    }

    if (curve_id == 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_KEY_SHARE,
                 SSL_R_NO_SUITABLE_KEY_SHARE);
        return EXT_RETURN_FAIL;
    }

    if (!add_key_share(s, pkt, curve_id)) {
        /* SSLfatal() already called */
        return EXT_RETURN_FAIL;
    }

    if (!WPACKET_close(pkt) || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_KEY_SHARE,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }
    return EXT_RETURN_SENT;
#else
    return EXT_RETURN_NOT_SENT;
#endif
}