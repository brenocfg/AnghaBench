#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_OID_set ;
typedef  int /*<<< orphan*/  gss_OID_desc ;
typedef  TYPE_2__* gss_OID ;
struct TYPE_11__ {int length; struct TYPE_11__* elements; } ;
struct TYPE_10__ {int count; TYPE_2__* elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ gss_test_oid_set_member (scalar_t__*,TYPE_2__* const,TYPE_1__*,int*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

OM_uint32
gss_add_oid_set_member(OM_uint32 *minor_status,
    const gss_OID member_oid,
    gss_OID_set *oid_set)
{
	OM_uint32 major_status;
	gss_OID_set set = *oid_set;
	gss_OID new_elements;
	gss_OID new_oid;
	int t;

	*minor_status = 0;

	major_status = gss_test_oid_set_member(minor_status,
	    member_oid, *oid_set, &t);
	if (major_status)
		return (major_status);
	if (t)
		return (GSS_S_COMPLETE);

	new_elements = malloc((set->count + 1) * sizeof(gss_OID_desc));
	if (!new_elements) {
		*minor_status = ENOMEM;
		return (GSS_S_FAILURE);
	}

	new_oid = &new_elements[set->count];
	new_oid->elements = malloc(member_oid->length);
	if (!new_oid->elements) {
		free(new_elements);
		return (GSS_S_FAILURE);
	}
	new_oid->length = member_oid->length;
	memcpy(new_oid->elements, member_oid->elements, member_oid->length);

	if (set->elements) {
		memcpy(new_elements, set->elements,
		    set->count * sizeof(gss_OID_desc));
		free(set->elements);
	}
	set->elements = new_elements;
	set->count++;

	return (GSS_S_COMPLETE);
}