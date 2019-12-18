#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t meths_count; TYPE_3__* meths; } ;
typedef  TYPE_2__ custom_ext_methods ;
struct TYPE_12__ {int ext_flags; int (* add_cb ) (TYPE_4__*,int /*<<< orphan*/ ,int,unsigned char const**,size_t*,int /*<<< orphan*/ *,size_t,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  add_arg; int /*<<< orphan*/  ext_type; int /*<<< orphan*/  (* free_cb ) (TYPE_4__*,int /*<<< orphan*/ ,int,unsigned char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; } ;
typedef  TYPE_3__ custom_ext_method ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_13__ {TYPE_1__* cert; } ;
struct TYPE_10__ {TYPE_2__ custext; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int SSL_AD_INTERNAL_ERROR ; 
 int SSL_EXT_CLIENT_HELLO ; 
 int SSL_EXT_FLAG_RECEIVED ; 
 int SSL_EXT_FLAG_SENT ; 
 int SSL_EXT_TLS1_2_SERVER_HELLO ; 
 int SSL_EXT_TLS1_3_CERTIFICATE ; 
 int SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS ; 
 int SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST ; 
 int SSL_EXT_TLS1_3_SERVER_HELLO ; 
 int /*<<< orphan*/  SSL_F_CUSTOM_EXT_ADD ; 
 int /*<<< orphan*/  SSL_R_CALLBACK_FAILED ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  should_add_extension (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,int,unsigned char const**,size_t*,int /*<<< orphan*/ *,size_t,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ,int,unsigned char const*,int /*<<< orphan*/ ) ; 

int custom_ext_add(SSL *s, int context, WPACKET *pkt, X509 *x, size_t chainidx,
                   int maxversion)
{
    custom_ext_methods *exts = &s->cert->custext;
    custom_ext_method *meth;
    size_t i;
    int al;

    for (i = 0; i < exts->meths_count; i++) {
        const unsigned char *out = NULL;
        size_t outlen = 0;

        meth = exts->meths + i;

        if (!should_add_extension(s, meth->context, context, maxversion))
            continue;

        if ((context & (SSL_EXT_TLS1_2_SERVER_HELLO
                        | SSL_EXT_TLS1_3_SERVER_HELLO
                        | SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS
                        | SSL_EXT_TLS1_3_CERTIFICATE
                        | SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST)) != 0) {
            /* Only send extensions present in ClientHello. */
            if (!(meth->ext_flags & SSL_EXT_FLAG_RECEIVED))
                continue;
        }
        /*
         * We skip it if the callback is absent - except for a ClientHello where
         * we add an empty extension.
         */
        if ((context & SSL_EXT_CLIENT_HELLO) == 0 && meth->add_cb == NULL)
            continue;

        if (meth->add_cb != NULL) {
            int cb_retval = meth->add_cb(s, meth->ext_type, context, &out,
                                         &outlen, x, chainidx, &al,
                                         meth->add_arg);

            if (cb_retval < 0) {
                SSLfatal(s, al, SSL_F_CUSTOM_EXT_ADD, SSL_R_CALLBACK_FAILED);
                return 0;       /* error */
            }
            if (cb_retval == 0)
                continue;       /* skip this extension */
        }

        if (!WPACKET_put_bytes_u16(pkt, meth->ext_type)
                || !WPACKET_start_sub_packet_u16(pkt)
                || (outlen > 0 && !WPACKET_memcpy(pkt, out, outlen))
                || !WPACKET_close(pkt)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_CUSTOM_EXT_ADD,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
        if ((context & SSL_EXT_CLIENT_HELLO) != 0) {
            /*
             * We can't send duplicates: code logic should prevent this.
             */
            if (!ossl_assert((meth->ext_flags & SSL_EXT_FLAG_SENT) == 0)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_CUSTOM_EXT_ADD,
                         ERR_R_INTERNAL_ERROR);
                return 0;
            }
            /*
             * Indicate extension has been sent: this is both a sanity check to
             * ensure we don't send duplicate extensions and indicates that it
             * is not an error if the extension is present in ServerHello.
             */
            meth->ext_flags |= SSL_EXT_FLAG_SENT;
        }
        if (meth->free_cb != NULL)
            meth->free_cb(s, meth->ext_type, context, out, meth->add_arg);
    }
    return 1;
}