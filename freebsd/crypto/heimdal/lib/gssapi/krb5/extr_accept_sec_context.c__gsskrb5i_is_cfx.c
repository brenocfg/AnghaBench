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
struct TYPE_7__ {int keytype; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_3__* gsskrb5_ctx ;
struct TYPE_8__ {int /*<<< orphan*/  crypto; int /*<<< orphan*/  more_flags; TYPE_1__* auth_context; } ;
struct TYPE_6__ {TYPE_2__* remote_subkey; TYPE_2__* local_subkey; TYPE_2__* keyblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPTOR_SUBKEY ; 
#define  ETYPE_ARCFOUR_HMAC_MD5 135 
#define  ETYPE_ARCFOUR_HMAC_MD5_56 134 
#define  ETYPE_DES3_CBC_MD5 133 
#define  ETYPE_DES3_CBC_SHA1 132 
#define  ETYPE_DES_CBC_CRC 131 
#define  ETYPE_DES_CBC_MD4 130 
#define  ETYPE_DES_CBC_MD5 129 
#define  ETYPE_OLD_DES3_CBC_SHA1 128 
 int /*<<< orphan*/  IS_CFX ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_crypto_init (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
_gsskrb5i_is_cfx(krb5_context context, gsskrb5_ctx ctx, int acceptor)
{
    krb5_error_code ret;
    krb5_keyblock *key;

    if (acceptor) {
	if (ctx->auth_context->local_subkey)
	    key = ctx->auth_context->local_subkey;
	else
	    key = ctx->auth_context->remote_subkey;
    } else {
	if (ctx->auth_context->remote_subkey)
	    key = ctx->auth_context->remote_subkey;
	else
	    key = ctx->auth_context->local_subkey;
    }
    if (key == NULL)
	key = ctx->auth_context->keyblock;

    if (key == NULL)
	return;

    switch (key->keytype) {
    case ETYPE_DES_CBC_CRC:
    case ETYPE_DES_CBC_MD4:
    case ETYPE_DES_CBC_MD5:
    case ETYPE_DES3_CBC_MD5:
    case ETYPE_OLD_DES3_CBC_SHA1:
    case ETYPE_DES3_CBC_SHA1:
    case ETYPE_ARCFOUR_HMAC_MD5:
    case ETYPE_ARCFOUR_HMAC_MD5_56:
	break;
    default :
        ctx->more_flags |= IS_CFX;

	if ((acceptor && ctx->auth_context->local_subkey) ||
	    (!acceptor && ctx->auth_context->remote_subkey))
	    ctx->more_flags |= ACCEPTOR_SUBKEY;
	break;
    }
    if (ctx->crypto)
        krb5_crypto_destroy(context, ctx->crypto);
    ret = krb5_crypto_init(context, key, 0, &ctx->crypto);
}