#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_11__ {TYPE_3__* s3; TYPE_2__* ctx; } ;
struct TYPE_10__ {int npn_seen; } ;
struct TYPE_8__ {int (* npn_advertised_cb ) (TYPE_4__*,unsigned char const**,unsigned int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  npn_advertised_cb_arg; } ;
struct TYPE_9__ {TYPE_1__ ext; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_STOC_NEXT_PROTO_NEG ; 
 int SSL_TLSEXT_ERR_OK ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_next_proto_neg ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u16 (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int stub1 (TYPE_4__*,unsigned char const**,unsigned int*,int /*<<< orphan*/ ) ; 

EXT_RETURN tls_construct_stoc_next_proto_neg(SSL *s, WPACKET *pkt,
                                             unsigned int context, X509 *x,
                                             size_t chainidx)
{
    const unsigned char *npa;
    unsigned int npalen;
    int ret;
    int npn_seen = s->s3->npn_seen;

    s->s3->npn_seen = 0;
    if (!npn_seen || s->ctx->ext.npn_advertised_cb == NULL)
        return EXT_RETURN_NOT_SENT;

    ret = s->ctx->ext.npn_advertised_cb(s, &npa, &npalen,
                                        s->ctx->ext.npn_advertised_cb_arg);
    if (ret == SSL_TLSEXT_ERR_OK) {
        if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_next_proto_neg)
                || !WPACKET_sub_memcpy_u16(pkt, npa, npalen)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_STOC_NEXT_PROTO_NEG,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
        s->s3->npn_seen = 1;
    }

    return EXT_RETURN_SENT;
}