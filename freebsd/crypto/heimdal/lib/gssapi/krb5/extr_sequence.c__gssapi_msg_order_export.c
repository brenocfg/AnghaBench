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
struct gss_msg_order {size_t flags; size_t start; size_t length; size_t jitter_window; size_t first_seq; size_t* elem; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  size_t OM_uint32 ;

/* Variables and functions */
 scalar_t__ krb5_store_int32 (int /*<<< orphan*/ *,size_t) ; 

krb5_error_code
_gssapi_msg_order_export(krb5_storage *sp, struct gss_msg_order *o)
{
    krb5_error_code kret;
    OM_uint32 i;

    kret = krb5_store_int32(sp, o->flags);
    if (kret)
        return kret;
    kret = krb5_store_int32(sp, o->start);
    if (kret)
        return kret;
    kret = krb5_store_int32(sp, o->length);
    if (kret)
        return kret;
    kret = krb5_store_int32(sp, o->jitter_window);
    if (kret)
        return kret;
    kret = krb5_store_int32(sp, o->first_seq);
    if (kret)
        return kret;

    for (i = 0; i < o->jitter_window; i++) {
        kret = krb5_store_int32(sp, o->elem[i]);
	if (kret)
	    return kret;
    }

    return 0;
}