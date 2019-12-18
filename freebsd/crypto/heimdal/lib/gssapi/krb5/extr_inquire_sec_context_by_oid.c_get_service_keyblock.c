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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  void* krb5_error_code ;
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  TYPE_2__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_buffer_set_t ;
struct TYPE_11__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ gss_buffer_desc ;
struct TYPE_10__ {int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/ * service_keyblock; } ;
typedef  void* OM_uint32 ;

/* Variables and functions */
 void* EINVAL ; 
 void* ENOMEM ; 
 void* GSS_S_COMPLETE ; 
 void* GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _gsskrb5_clear_status () ; 
 int /*<<< orphan*/  _gsskrb5_set_status (void*,char*) ; 
 void* gss_add_buffer_set_member (void**,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 void* krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* krb5_store_keyblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
get_service_keyblock
        (OM_uint32 *minor_status,
	 gsskrb5_ctx ctx,
	 gss_buffer_set_t *data_set)
{
    krb5_storage *sp = NULL;
    krb5_data data;
    OM_uint32 maj_stat = GSS_S_COMPLETE;
    krb5_error_code ret = EINVAL;

    sp = krb5_storage_emem();
    if (sp == NULL) {
	_gsskrb5_clear_status();
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    HEIMDAL_MUTEX_lock(&ctx->ctx_id_mutex);
    if (ctx->service_keyblock == NULL) {
	HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);
	krb5_storage_free(sp);
	_gsskrb5_set_status(EINVAL, "No service keyblock on gssapi context");
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }

    krb5_data_zero(&data);

    ret = krb5_store_keyblock(sp, *ctx->service_keyblock);

    HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);

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