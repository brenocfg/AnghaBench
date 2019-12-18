#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  custom_ext_methods ;
struct TYPE_10__ {int ext_flags; scalar_t__ (* parse_cb ) (TYPE_3__*,unsigned int,unsigned int,unsigned char const*,size_t,int /*<<< orphan*/ *,size_t,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  parse_arg; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ custom_ext_method ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_11__ {scalar_t__ server; TYPE_1__* cert; } ;
struct TYPE_9__ {int /*<<< orphan*/  custext; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  ENDPOINT ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPOINT_BOTH ; 
 int /*<<< orphan*/  ENDPOINT_CLIENT ; 
 int /*<<< orphan*/  ENDPOINT_SERVER ; 
 unsigned int SSL_EXT_CLIENT_HELLO ; 
 int SSL_EXT_FLAG_RECEIVED ; 
 int SSL_EXT_FLAG_SENT ; 
 unsigned int SSL_EXT_TLS1_2_SERVER_HELLO ; 
 unsigned int SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS ; 
 unsigned int SSL_EXT_TLS1_3_SERVER_HELLO ; 
 int /*<<< orphan*/  SSL_F_CUSTOM_EXT_PARSE ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS1_AD_UNSUPPORTED_EXTENSION ; 
 TYPE_2__* custom_ext_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extension_is_relevant (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ stub1 (TYPE_3__*,unsigned int,unsigned int,unsigned char const*,size_t,int /*<<< orphan*/ *,size_t,int*,int /*<<< orphan*/ ) ; 

int custom_ext_parse(SSL *s, unsigned int context, unsigned int ext_type,
                     const unsigned char *ext_data, size_t ext_size, X509 *x,
                     size_t chainidx)
{
    int al;
    custom_ext_methods *exts = &s->cert->custext;
    custom_ext_method *meth;
    ENDPOINT role = ENDPOINT_BOTH;

    if ((context & (SSL_EXT_CLIENT_HELLO | SSL_EXT_TLS1_2_SERVER_HELLO)) != 0)
        role = s->server ? ENDPOINT_SERVER : ENDPOINT_CLIENT;

    meth = custom_ext_find(exts, role, ext_type, NULL);
    /* If not found return success */
    if (!meth)
        return 1;

    /* Check if extension is defined for our protocol. If not, skip */
    if (!extension_is_relevant(s, meth->context, context))
        return 1;

    if ((context & (SSL_EXT_TLS1_2_SERVER_HELLO
                    | SSL_EXT_TLS1_3_SERVER_HELLO
                    | SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS)) != 0) {
        /*
         * If it's ServerHello or EncryptedExtensions we can't have any
         * extensions not sent in ClientHello.
         */
        if ((meth->ext_flags & SSL_EXT_FLAG_SENT) == 0) {
            SSLfatal(s, TLS1_AD_UNSUPPORTED_EXTENSION, SSL_F_CUSTOM_EXT_PARSE,
                     SSL_R_BAD_EXTENSION);
            return 0;
        }
    }

    /*
     * Extensions received in the ClientHello are marked with the
     * SSL_EXT_FLAG_RECEIVED. This is so we know to add the equivalent
     * extensions in the ServerHello/EncryptedExtensions message
     */
    if ((context & SSL_EXT_CLIENT_HELLO) != 0)
        meth->ext_flags |= SSL_EXT_FLAG_RECEIVED;

    /* If no parse function set return success */
    if (!meth->parse_cb)
        return 1;

    if (meth->parse_cb(s, ext_type, context, ext_data, ext_size, x, chainidx,
                       &al, meth->parse_arg) <= 0) {
        SSLfatal(s, al, SSL_F_CUSTOM_EXT_PARSE, SSL_R_BAD_EXTENSION);
        return 0;
    }

    return 1;
}