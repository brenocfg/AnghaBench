#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_5__ {int /*<<< orphan*/  psk_kex_mode; } ;
struct TYPE_6__ {int options; TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_PSK_KEX_MODES ; 
 int SSL_OP_ALLOW_NO_DHE_KEX ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_KEX_MODE_FLAG_KE ; 
 int /*<<< orphan*/  TLSEXT_KEX_MODE_FLAG_KE_DHE ; 
 int /*<<< orphan*/  TLSEXT_KEX_MODE_KE ; 
 int /*<<< orphan*/  TLSEXT_KEX_MODE_KE_DHE ; 
 int /*<<< orphan*/  TLSEXT_TYPE_psk_kex_modes ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u8 (int /*<<< orphan*/ *) ; 

EXT_RETURN tls_construct_ctos_psk_kex_modes(SSL *s, WPACKET *pkt,
                                            unsigned int context, X509 *x,
                                            size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    int nodhe = s->options & SSL_OP_ALLOW_NO_DHE_KEX;

    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_psk_kex_modes)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_start_sub_packet_u8(pkt)
            || !WPACKET_put_bytes_u8(pkt, TLSEXT_KEX_MODE_KE_DHE)
            || (nodhe && !WPACKET_put_bytes_u8(pkt, TLSEXT_KEX_MODE_KE))
            || !WPACKET_close(pkt)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_PSK_KEX_MODES, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    s->ext.psk_kex_mode = TLSEXT_KEX_MODE_FLAG_KE_DHE;
    if (nodhe)
        s->ext.psk_kex_mode |= TLSEXT_KEX_MODE_FLAG_KE;
#endif

    return EXT_RETURN_SENT;
}