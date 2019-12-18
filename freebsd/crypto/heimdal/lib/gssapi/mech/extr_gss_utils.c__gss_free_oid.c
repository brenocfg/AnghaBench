#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_OID ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/ * elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

OM_uint32
_gss_free_oid(OM_uint32 *minor_status, gss_OID oid)
{
	*minor_status = 0;
	if (oid->elements) {
	    free(oid->elements);
	    oid->elements = NULL;
	    oid->length = 0;
	}
	return (GSS_S_COMPLETE);
}