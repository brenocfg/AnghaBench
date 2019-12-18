#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_12__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_2__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_buffer_set_t ;
struct TYPE_14__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ gss_buffer_desc ;
typedef  enum keytype { ____Placeholder_keytype } keytype ;
struct TYPE_13__ {int /*<<< orphan*/  ctx_id_mutex; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
#define  ACCEPTOR_KEY 130 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
#define  INITIATOR_KEY 129 
#define  TOKEN_KEY 128 
 int /*<<< orphan*/  _gsskrb5_clear_status () ; 
 int /*<<< orphan*/  _gsskrb5_set_status (scalar_t__,char*,int) ; 
 scalar_t__ _gsskrb5i_get_acceptor_subkey (TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ _gsskrb5i_get_initiator_subkey (TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ _gsskrb5i_get_token_key (TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ gss_add_buffer_set_member (scalar_t__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ krb5_store_keyblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32 inquire_sec_context_get_subkey
           (OM_uint32 *minor_status,
            const gsskrb5_ctx context_handle,
	    krb5_context context,
	    enum keytype keytype,
            gss_buffer_set_t *data_set)
{
    krb5_keyblock *key = NULL;
    krb5_storage *sp = NULL;
    krb5_data data;
    OM_uint32 maj_stat = GSS_S_COMPLETE;
    krb5_error_code ret;

    krb5_data_zero(&data);

    sp = krb5_storage_emem();
    if (sp == NULL) {
	_gsskrb5_clear_status();
	ret = ENOMEM;
	goto out;
    }

    HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);
    switch(keytype) {
    case ACCEPTOR_KEY:
	ret = _gsskrb5i_get_acceptor_subkey(context_handle, context, &key);
	break;
    case INITIATOR_KEY:
	ret = _gsskrb5i_get_initiator_subkey(context_handle, context, &key);
	break;
    case TOKEN_KEY:
	ret = _gsskrb5i_get_token_key(context_handle, context, &key);
	break;
    default:
	_gsskrb5_set_status(EINVAL, "%d is not a valid subkey type", keytype);
	ret = EINVAL;
	break;
   }
    HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
    if (ret)
	goto out;
    if (key == NULL) {
	_gsskrb5_set_status(EINVAL, "have no subkey of type %d", keytype);
	ret = EINVAL;
	goto out;
    }

    ret = krb5_store_keyblock(sp, *key);
    krb5_free_keyblock (context, key);
    if (ret)
	goto out;

    ret = krb5_storage_to_data(sp, &data);
    if (ret)
	goto out;

    {
	gss_buffer_desc value;

	value.length = data.length;
	value.value = data.data;

	maj_stat = gss_add_buffer_set_member(minor_status,
					     &value,
					     data_set);
    }

out:
    krb5_data_free(&data);
    if (sp)
	krb5_storage_free(sp);
    if (ret) {
	*minor_status = ret;
	maj_stat = GSS_S_FAILURE;
    }
    return maj_stat;
}