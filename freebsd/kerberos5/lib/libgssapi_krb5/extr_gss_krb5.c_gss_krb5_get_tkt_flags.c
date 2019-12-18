#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  TYPE_2__* gss_buffer_set_t ;
struct TYPE_7__ {int count; TYPE_1__* elements; } ;
struct TYPE_6__ {int length; int* value; } ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* GSS_C_NO_BUFFER_SET ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 int /*<<< orphan*/  GSS_KRB5_GET_TKT_FLAGS_X ; 
 int GSS_S_COMPLETE ; 
 int GSS_S_FAILURE ; 
 int gss_inquire_sec_context_by_oid (int*,scalar_t__,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  gss_release_buffer_set (int*,TYPE_2__**) ; 

OM_uint32
gss_krb5_get_tkt_flags(OM_uint32 *minor_status,
		       gss_ctx_id_t context_handle,
		       OM_uint32 *tkt_flags)
{

    OM_uint32 major_status;
    gss_buffer_set_t data_set = GSS_C_NO_BUFFER_SET;

    if (context_handle == GSS_C_NO_CONTEXT) {
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }
    
    major_status =
	gss_inquire_sec_context_by_oid (minor_status,
					context_handle,
					GSS_KRB5_GET_TKT_FLAGS_X,
					&data_set);
    if (major_status)
	return major_status;
    
    if (data_set == GSS_C_NO_BUFFER_SET || 
	data_set->count != 1 ||
	data_set->elements[0].length < 4) {
	gss_release_buffer_set(minor_status, &data_set);
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }

    {
	const u_char *p = data_set->elements[0].value;
	*tkt_flags = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
    }

    gss_release_buffer_set(minor_status, &data_set);
    return GSS_S_COMPLETE;
}