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
struct gss_msg_order {scalar_t__* elem; scalar_t__ jitter_window; scalar_t__ first_seq; scalar_t__ length; scalar_t__ flags; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ DEFAULT_JITTER_WINDOW ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ msg_order_alloc (scalar_t__*,struct gss_msg_order**,scalar_t__) ; 

OM_uint32
_gssapi_msg_order_create(OM_uint32 *minor_status,
			 struct gss_msg_order **o,
			 OM_uint32 flags,
			 OM_uint32 seq_num,
			 OM_uint32 jitter_window,
			 int use_64)
{
    OM_uint32 ret;

    if (jitter_window == 0)
	jitter_window = DEFAULT_JITTER_WINDOW;

    ret = msg_order_alloc(minor_status, o, jitter_window);
    if(ret != GSS_S_COMPLETE)
        return ret;

    (*o)->flags = flags;
    (*o)->length = 0;
    (*o)->first_seq = seq_num;
    (*o)->jitter_window = jitter_window;
    (*o)->elem[0] = seq_num - 1;

    *minor_status = 0;
    return GSS_S_COMPLETE;
}