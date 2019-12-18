#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  TYPE_2__* gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_6__ {int /*<<< orphan*/ * value; int /*<<< orphan*/  length; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ _gssapi_verify_mech_header (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

OM_uint32
_gssapi_decapsulate(
    OM_uint32 *minor_status,
    gss_buffer_t input_token_buffer,
    krb5_data *out_data,
    const gss_OID mech
)
{
    u_char *p;
    OM_uint32 ret;

    p = input_token_buffer->value;
    ret = _gssapi_verify_mech_header(&p,
				    input_token_buffer->length,
				    mech);
    if (ret) {
	*minor_status = 0;
	return ret;
    }

    out_data->length = input_token_buffer->length -
	(p - (u_char *)input_token_buffer->value);
    out_data->data   = p;
    return GSS_S_COMPLETE;
}