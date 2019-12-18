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
typedef  int /*<<< orphan*/  gss_OID_set_desc ;
typedef  TYPE_1__* gss_OID_set ;
struct TYPE_5__ {scalar_t__ elements; scalar_t__ count; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 TYPE_1__* GSS_C_NO_OID_SET ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 TYPE_1__* malloc (int) ; 

OM_uint32
gss_create_empty_oid_set(OM_uint32 *minor_status,
    gss_OID_set *oid_set)
{
	gss_OID_set set;

	*minor_status = 0;
	*oid_set = GSS_C_NO_OID_SET;

	set = malloc(sizeof(gss_OID_set_desc));
	if (!set) {
		*minor_status = ENOMEM;
		return (GSS_S_FAILURE);
	}

	set->count = 0;
	set->elements = 0;
	*oid_set = set;

	return (GSS_S_COMPLETE);
}