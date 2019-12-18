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
struct TYPE_5__ {scalar_t__ ctx; } ;
typedef  TYPE_1__ gss_mo_desc ;
typedef  int /*<<< orphan*/  gss_const_OID ;
typedef  TYPE_2__* gss_buffer_t ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int GSS_S_COMPLETE ; 
 int GSS_S_FAILURE ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
_gss_mo_get_ctx_as_string(gss_const_OID mech, gss_mo_desc *mo, gss_buffer_t value)
{
    if (value) {
	value->value = strdup((char *)mo->ctx);
	if (value->value == NULL)
	    return GSS_S_FAILURE;
	value->length = strlen((char *)mo->ctx);
    }
    return GSS_S_COMPLETE;
}