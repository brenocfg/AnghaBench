#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_OID_set ;
typedef  TYPE_1__* gss_OID ;
struct TYPE_6__ {size_t count; struct TYPE_6__* elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 TYPE_1__* GSS_C_NO_OID_SET ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

OM_uint32
gss_release_oid_set(OM_uint32 *minor_status,
    gss_OID_set *setp)
{
	gss_OID_set set;
	gss_OID o;
	size_t i;

	*minor_status = 0;
	if (setp) {
		set = *setp;
		if (set) {
			for (i = 0; i < set->count; i++) {
				o = &set->elements[i];
				if (o->elements)
					free(o->elements);
			}
			free(set->elements);
			free(set);
			*setp = GSS_C_NO_OID_SET;
		}
	}
	return (GSS_S_COMPLETE);
}