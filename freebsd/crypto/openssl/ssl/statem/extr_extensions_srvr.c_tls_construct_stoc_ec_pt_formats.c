#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_11__ {int /*<<< orphan*/ * peer_ecpointformats; } ;
struct TYPE_13__ {TYPE_3__ ext; TYPE_2__* s3; } ;
struct TYPE_12__ {unsigned long algorithm_mkey; unsigned long algorithm_auth; } ;
struct TYPE_9__ {TYPE_4__* new_cipher; } ;
struct TYPE_10__ {TYPE_1__ tmp; } ;
typedef  TYPE_5__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_STOC_EC_PT_FORMATS ; 
 unsigned long SSL_aECDSA ; 
 unsigned long SSL_kECDHE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_ec_point_formats ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  tls1_get_formatlist (TYPE_5__*,unsigned char const**,size_t*) ; 

EXT_RETURN tls_construct_stoc_ec_pt_formats(SSL *s, WPACKET *pkt,
                                            unsigned int context, X509 *x,
                                            size_t chainidx)
{
    unsigned long alg_k = s->s3->tmp.new_cipher->algorithm_mkey;
    unsigned long alg_a = s->s3->tmp.new_cipher->algorithm_auth;
    int using_ecc = ((alg_k & SSL_kECDHE) || (alg_a & SSL_aECDSA))
                    && (s->ext.peer_ecpointformats != NULL);
    const unsigned char *plist;
    size_t plistlen;

    if (!using_ecc)
        return EXT_RETURN_NOT_SENT;

    tls1_get_formatlist(s, &plist, &plistlen);
    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_ec_point_formats)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_sub_memcpy_u8(pkt, plist, plistlen)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_STOC_EC_PT_FORMATS, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}