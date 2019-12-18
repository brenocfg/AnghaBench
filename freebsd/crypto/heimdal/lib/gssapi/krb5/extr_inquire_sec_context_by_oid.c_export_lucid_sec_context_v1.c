#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_13__ {int keytype; } ;
typedef  TYPE_1__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ int32_t ;
typedef  TYPE_3__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_buffer_set_t ;
struct TYPE_16__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ gss_buffer_desc ;
struct TYPE_15__ {int more_flags; int lifetime; int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/  auth_context; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int ACCEPTOR_SUBKEY ; 
 scalar_t__ ENOMEM ; 
#define  ETYPE_ARCFOUR_HMAC_MD5 134 
#define  ETYPE_ARCFOUR_HMAC_MD5_56 133 
#define  ETYPE_DES3_CBC_MD5 132 
#define  ETYPE_DES3_CBC_SHA1 131 
#define  ETYPE_DES_CBC_CRC 130 
#define  ETYPE_DES_CBC_MD4 129 
#define  ETYPE_DES_CBC_MD5 128 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int IS_CFX ; 
 int LOCAL ; 
 int /*<<< orphan*/  _gsskrb5_clear_status () ; 
 scalar_t__ _gsskrb5i_get_token_key (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ gss_add_buffer_set_member (scalar_t__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_auth_con_getlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_auth_con_getremoteseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ krb5_store_int32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ krb5_store_keyblock (int /*<<< orphan*/ *,TYPE_1__) ; 
 scalar_t__ krb5_store_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
export_lucid_sec_context_v1(OM_uint32 *minor_status,
			    gsskrb5_ctx context_handle,
			    krb5_context context,
			    gss_buffer_set_t *data_set)
{
    krb5_storage *sp = NULL;
    OM_uint32 major_status = GSS_S_COMPLETE;
    krb5_error_code ret;
    krb5_keyblock *key = NULL;
    int32_t number;
    int is_cfx;
    krb5_data data;

    *minor_status = 0;

    HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);

    is_cfx = (context_handle->more_flags & IS_CFX);

    sp = krb5_storage_emem();
    if (sp == NULL) {
	_gsskrb5_clear_status();
	ret = ENOMEM;
	goto out;
    }

    ret = krb5_store_int32(sp, 1);
    if (ret) goto out;
    ret = krb5_store_int32(sp, (context_handle->more_flags & LOCAL) ? 1 : 0);
    if (ret) goto out;
    ret = krb5_store_int32(sp, context_handle->lifetime);
    if (ret) goto out;
    krb5_auth_con_getlocalseqnumber (context,
				     context_handle->auth_context,
				     &number);
    ret = krb5_store_uint32(sp, (uint32_t)0); /* store top half as zero */
    if (ret) goto out;
    ret = krb5_store_uint32(sp, (uint32_t)number);
    if (ret) goto out;
    krb5_auth_con_getremoteseqnumber (context,
				      context_handle->auth_context,
				      &number);
    ret = krb5_store_uint32(sp, (uint32_t)0); /* store top half as zero */
    if (ret) goto out;
    ret = krb5_store_uint32(sp, (uint32_t)number);
    if (ret) goto out;
    ret = krb5_store_int32(sp, (is_cfx) ? 1 : 0);
    if (ret) goto out;

    ret = _gsskrb5i_get_token_key(context_handle, context, &key);
    if (ret) goto out;

    if (is_cfx == 0) {
	int sign_alg, seal_alg;

	switch (key->keytype) {
	case ETYPE_DES_CBC_CRC:
	case ETYPE_DES_CBC_MD4:
	case ETYPE_DES_CBC_MD5:
	    sign_alg = 0;
	    seal_alg = 0;
	    break;
	case ETYPE_DES3_CBC_MD5:
	case ETYPE_DES3_CBC_SHA1:
	    sign_alg = 4;
	    seal_alg = 2;
	    break;
	case ETYPE_ARCFOUR_HMAC_MD5:
	case ETYPE_ARCFOUR_HMAC_MD5_56:
	    sign_alg = 17;
	    seal_alg = 16;
	    break;
	default:
	    sign_alg = -1;
	    seal_alg = -1;
	    break;
	}
	ret = krb5_store_int32(sp, sign_alg);
	if (ret) goto out;
	ret = krb5_store_int32(sp, seal_alg);
	if (ret) goto out;
	/* ctx_key */
	ret = krb5_store_keyblock(sp, *key);
	if (ret) goto out;
    } else {
	int subkey_p = (context_handle->more_flags & ACCEPTOR_SUBKEY) ? 1 : 0;

	/* have_acceptor_subkey */
	ret = krb5_store_int32(sp, subkey_p);
	if (ret) goto out;
	/* ctx_key */
	ret = krb5_store_keyblock(sp, *key);
	if (ret) goto out;
	/* acceptor_subkey */
	if (subkey_p) {
	    ret = krb5_store_keyblock(sp, *key);
	    if (ret) goto out;
	}
    }
    ret = krb5_storage_to_data(sp, &data);
    if (ret) goto out;

    {
	gss_buffer_desc ad_data;

	ad_data.value = data.data;
	ad_data.length = data.length;

	ret = gss_add_buffer_set_member(minor_status, &ad_data, data_set);
	krb5_data_free(&data);
	if (ret)
	    goto out;
    }

out:
    if (key)
	krb5_free_keyblock (context, key);
    if (sp)
	krb5_storage_free(sp);
    if (ret) {
	*minor_status = ret;
	major_status = GSS_S_FAILURE;
    }
    HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
    return major_status;
}