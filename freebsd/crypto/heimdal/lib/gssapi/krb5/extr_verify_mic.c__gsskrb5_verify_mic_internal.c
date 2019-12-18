#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int krb5_keytype ;
struct TYPE_14__ {int /*<<< orphan*/  keytype; } ;
typedef  TYPE_1__ krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_2__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
struct TYPE_15__ {int more_flags; int /*<<< orphan*/  ctx_id_mutex; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int IS_CFX ; 
#define  KEYTYPE_ARCFOUR 131 
#define  KEYTYPE_ARCFOUR_56 130 
#define  KEYTYPE_DES 129 
#define  KEYTYPE_DES3 128 
 scalar_t__ _gssapi_verify_mic_arcfour (scalar_t__*,TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 
 scalar_t__ _gssapi_verify_mic_cfx (scalar_t__*,TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 scalar_t__ _gsskrb5i_get_token_key (TYPE_2__* const,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  krb5_enctype_to_keytype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ verify_mic_des (scalar_t__*,TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 
 scalar_t__ verify_mic_des3 (scalar_t__*,TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 

OM_uint32
_gsskrb5_verify_mic_internal
           (OM_uint32 * minor_status,
            const gsskrb5_ctx ctx,
	    krb5_context context,
            const gss_buffer_t message_buffer,
            const gss_buffer_t token_buffer,
            gss_qop_t * qop_state,
	    const char * type
	    )
{
    krb5_keyblock *key;
    OM_uint32 ret;
    krb5_keytype keytype;

    if (ctx->more_flags & IS_CFX)
        return _gssapi_verify_mic_cfx (minor_status, ctx,
				       context, message_buffer, token_buffer,
				       qop_state);

    HEIMDAL_MUTEX_lock(&ctx->ctx_id_mutex);
    ret = _gsskrb5i_get_token_key(ctx, context, &key);
    HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);
    if (ret) {
	*minor_status = ret;
	return GSS_S_FAILURE;
    }
    *minor_status = 0;
    krb5_enctype_to_keytype (context, key->keytype, &keytype);
    switch (keytype) {
    case KEYTYPE_DES :
#ifdef HEIM_WEAK_CRYPTO
	ret = verify_mic_des (minor_status, ctx, context,
			      message_buffer, token_buffer, qop_state, key,
			      type);
#else
      ret = GSS_S_FAILURE;
#endif
	break;
    case KEYTYPE_DES3 :
	ret = verify_mic_des3 (minor_status, ctx, context,
			       message_buffer, token_buffer, qop_state, key,
			       type);
	break;
    case KEYTYPE_ARCFOUR :
    case KEYTYPE_ARCFOUR_56 :
	ret = _gssapi_verify_mic_arcfour (minor_status, ctx,
					  context,
					  message_buffer, token_buffer,
					  qop_state, key, type);
	break;
    default :
        abort();
    }
    krb5_free_keyblock (context, key);

    return ret;
}