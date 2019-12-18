#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_11__ {scalar_t__ use_etm; } ;
struct TYPE_12__ {TYPE_4__ ext; TYPE_3__* s3; } ;
struct TYPE_9__ {TYPE_1__* new_cipher; } ;
struct TYPE_10__ {TYPE_2__ tmp; } ;
struct TYPE_8__ {scalar_t__ algorithm_mac; scalar_t__ algorithm_enc; } ;
typedef  TYPE_5__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 scalar_t__ SSL_AEAD ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_STOC_ETM ; 
 scalar_t__ SSL_RC4 ; 
 scalar_t__ SSL_eGOST2814789CNT ; 
 scalar_t__ SSL_eGOST2814789CNT12 ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_encrypt_then_mac ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

EXT_RETURN tls_construct_stoc_etm(SSL *s, WPACKET *pkt, unsigned int context,
                                  X509 *x, size_t chainidx)
{
    if (!s->ext.use_etm)
        return EXT_RETURN_NOT_SENT;

    /*
     * Don't use encrypt_then_mac if AEAD or RC4 might want to disable
     * for other cases too.
     */
    if (s->s3->tmp.new_cipher->algorithm_mac == SSL_AEAD
        || s->s3->tmp.new_cipher->algorithm_enc == SSL_RC4
        || s->s3->tmp.new_cipher->algorithm_enc == SSL_eGOST2814789CNT
        || s->s3->tmp.new_cipher->algorithm_enc == SSL_eGOST2814789CNT12) {
        s->ext.use_etm = 0;
        return EXT_RETURN_NOT_SENT;
    }

    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_encrypt_then_mac)
            || !WPACKET_put_bytes_u16(pkt, 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_ETM,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}