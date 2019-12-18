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
typedef  int OM_uint32 ;

/* Variables and functions */
 int GSS_C_REPLAY_FLAG ; 
 int GSS_C_SEQUENCE_FLAG ; 

OM_uint32
_gssapi_msg_order_f(OM_uint32 flags)
{
    return flags & (GSS_C_SEQUENCE_FLAG|GSS_C_REPLAY_FLAG);
}