#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_OID ;
struct TYPE_5__ {scalar_t__ length; struct TYPE_5__* elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 TYPE_1__* GSS_C_NO_OID ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

OM_uint32
gss_release_oid(OM_uint32 *minor_status, gss_OID *oid)
{
	gss_OID o = *oid;

	*oid = GSS_C_NO_OID;

	if (minor_status != NULL)
		*minor_status = 0;

	if (o == GSS_C_NO_OID)
		return (GSS_S_COMPLETE);

	if (o->elements != NULL) {
		free(o->elements);
		o->elements = NULL;
	}
	o->length = 0;
	free(o);

	return (GSS_S_COMPLETE);
}