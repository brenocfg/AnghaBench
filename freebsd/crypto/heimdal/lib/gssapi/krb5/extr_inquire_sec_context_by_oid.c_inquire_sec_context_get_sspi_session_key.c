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
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {TYPE_1__ keyvalue; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_3__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_buffer_set_t ;
struct TYPE_13__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; } ;
typedef  TYPE_4__ gss_buffer_desc ;
struct TYPE_12__ {int /*<<< orphan*/  ctx_id_mutex; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ _gsskrb5i_get_token_key (TYPE_3__* const,int /*<<< orphan*/ ,TYPE_2__**) ; 
 scalar_t__ gss_add_buffer_set_member (scalar_t__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static OM_uint32 inquire_sec_context_get_sspi_session_key
            (OM_uint32 *minor_status,
             const gsskrb5_ctx context_handle,
             krb5_context context,
             gss_buffer_set_t *data_set)
{
    krb5_keyblock *key;
    OM_uint32 maj_stat = GSS_S_COMPLETE;
    krb5_error_code ret;
    gss_buffer_desc value;

    HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);
    ret = _gsskrb5i_get_token_key(context_handle, context, &key);
    HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);

    if (ret)
        goto out;
    if (key == NULL) {
        ret = EINVAL;
        goto out;
    }

    value.length = key->keyvalue.length;
    value.value = key->keyvalue.data;

    maj_stat = gss_add_buffer_set_member(minor_status,
                                         &value,
                                         data_set);
    krb5_free_keyblock(context, key);

    /* MIT also returns the enctype encoded as an OID in data_set[1] */

out:
    if (ret) {
        *minor_status = ret;
        maj_stat = GSS_S_FAILURE;
    }
    return maj_stat;
}