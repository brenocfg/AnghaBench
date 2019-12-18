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
struct gss_msg_order {int flags; int* elem; int first_seq; int length; } ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int GSS_C_REPLAY_FLAG ; 
 int GSS_C_SEQUENCE_FLAG ; 
 int GSS_S_COMPLETE ; 
 int GSS_S_DUPLICATE_TOKEN ; 
 int GSS_S_FAILURE ; 
 int GSS_S_GAP_TOKEN ; 
 int GSS_S_OLD_TOKEN ; 
 int GSS_S_UNSEQ_TOKEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  elem_insert (struct gss_msg_order*,size_t,int) ; 

OM_uint32
_gssapi_msg_order_check(struct gss_msg_order *o, OM_uint32 seq_num)
{
    OM_uint32 r;
    size_t i;

    if (o == NULL)
	return GSS_S_COMPLETE;

    if ((o->flags & (GSS_C_REPLAY_FLAG|GSS_C_SEQUENCE_FLAG)) == 0)
	return GSS_S_COMPLETE;

    /* check if the packet is the next in order */
    if (o->elem[0] == seq_num - 1) {
	elem_insert(o, 0, seq_num);
	return GSS_S_COMPLETE;
    }

    r = (o->flags & (GSS_C_REPLAY_FLAG|GSS_C_SEQUENCE_FLAG))==GSS_C_REPLAY_FLAG;

    /* sequence number larger then largest sequence number
     * or smaller then the first sequence number */
    if (seq_num > o->elem[0]
	|| seq_num < o->first_seq
	|| o->length == 0)
    {
	elem_insert(o, 0, seq_num);
	if (r) {
	    return GSS_S_COMPLETE;
	} else {
	    return GSS_S_GAP_TOKEN;
	}
    }

    assert(o->length > 0);

    /* sequence number smaller the first sequence number */
    if (seq_num < o->elem[o->length - 1]) {
	if (r)
	    return(GSS_S_OLD_TOKEN);
	else
	    return(GSS_S_UNSEQ_TOKEN);
    }

    if (seq_num == o->elem[o->length - 1]) {
	return GSS_S_DUPLICATE_TOKEN;
    }

    for (i = 0; i < o->length - 1; i++) {
	if (o->elem[i] == seq_num)
	    return GSS_S_DUPLICATE_TOKEN;
	if (o->elem[i + 1] < seq_num && o->elem[i] < seq_num) {
	    elem_insert(o, i, seq_num);
	    if (r)
		return GSS_S_COMPLETE;
	    else
		return GSS_S_UNSEQ_TOKEN;
	}
    }

    return GSS_S_FAILURE;
}