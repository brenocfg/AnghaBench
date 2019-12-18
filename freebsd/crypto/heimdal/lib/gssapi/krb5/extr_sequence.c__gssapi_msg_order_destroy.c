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
struct gss_msg_order {int dummy; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  free (struct gss_msg_order*) ; 

OM_uint32
_gssapi_msg_order_destroy(struct gss_msg_order **m)
{
    free(*m);
    *m = NULL;
    return GSS_S_COMPLETE;
}