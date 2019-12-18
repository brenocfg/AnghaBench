#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gss_msg_order {size_t flags; size_t start; size_t length; size_t jitter_window; size_t first_seq; int /*<<< orphan*/ * elem; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  size_t int32_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  _gssapi_msg_order_destroy (struct gss_msg_order**) ; 
 scalar_t__ krb5_ret_int32 (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ msg_order_alloc (scalar_t__*,struct gss_msg_order**,size_t) ; 

OM_uint32
_gssapi_msg_order_import(OM_uint32 *minor_status,
			 krb5_storage *sp,
			 struct gss_msg_order **o)
{
    OM_uint32 ret;
    krb5_error_code kret;
    int32_t i, flags, start, length, jitter_window, first_seq;

    kret = krb5_ret_int32(sp, &flags);
    if (kret)
	goto failed;
    kret = krb5_ret_int32(sp, &start);
    if (kret)
	goto failed;
    kret = krb5_ret_int32(sp, &length);
    if (kret)
	goto failed;
    kret = krb5_ret_int32(sp, &jitter_window);
    if (kret)
	goto failed;
    kret = krb5_ret_int32(sp, &first_seq);
    if (kret)
	goto failed;

    ret = msg_order_alloc(minor_status, o, jitter_window);
    if (ret != GSS_S_COMPLETE)
        return ret;

    (*o)->flags = flags;
    (*o)->start = start;
    (*o)->length = length;
    (*o)->jitter_window = jitter_window;
    (*o)->first_seq = first_seq;

    for( i = 0; i < jitter_window; i++ ) {
        kret = krb5_ret_int32(sp, (int32_t*)&((*o)->elem[i]));
	if (kret)
	    goto failed;
    }

    *minor_status = 0;
    return GSS_S_COMPLETE;

failed:
    _gssapi_msg_order_destroy(o);
    *minor_status = kret;
    return GSS_S_FAILURE;
}