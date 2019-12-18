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
struct TYPE_5__ {int /*<<< orphan*/  psk_kex_mode; } ;
struct TYPE_6__ {int options; TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_as_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_PSK_KEX_MODES ; 
 int SSL_OP_ALLOW_NO_DHE_KEX ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_KEX_MODE_FLAG_KE ; 
 int /*<<< orphan*/  TLSEXT_KEX_MODE_FLAG_KE_DHE ; 
 unsigned int TLSEXT_KEX_MODE_KE ; 
 unsigned int TLSEXT_KEX_MODE_KE_DHE ; 

int tls_parse_ctos_psk_kex_modes(SSL *s, PACKET *pkt, unsigned int context,
                                 X509 *x, size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    PACKET psk_kex_modes;
    unsigned int mode;

    if (!PACKET_as_length_prefixed_1(pkt, &psk_kex_modes)
            || PACKET_remaining(&psk_kex_modes) == 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_PSK_KEX_MODES,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    while (PACKET_get_1(&psk_kex_modes, &mode)) {
        if (mode == TLSEXT_KEX_MODE_KE_DHE)
            s->ext.psk_kex_mode |= TLSEXT_KEX_MODE_FLAG_KE_DHE;
        else if (mode == TLSEXT_KEX_MODE_KE
                && (s->options & SSL_OP_ALLOW_NO_DHE_KEX) != 0)
            s->ext.psk_kex_mode |= TLSEXT_KEX_MODE_FLAG_KE;
    }
#endif

    return 1;
}