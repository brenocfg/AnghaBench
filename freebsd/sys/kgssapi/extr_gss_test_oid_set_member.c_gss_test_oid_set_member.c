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
typedef  TYPE_1__* gss_OID_set ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_3__ {size_t count; int /*<<< orphan*/ * elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ kgss_oid_equal (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

OM_uint32
gss_test_oid_set_member(OM_uint32 *minor_status,
    const gss_OID member,
    const gss_OID_set set,
    int *present)
{
	size_t i;

	*present = 0;
	for (i = 0; i < set->count; i++)
		if (kgss_oid_equal(member, &set->elements[i]))
			*present = 1;

	*minor_status = 0;
	return (GSS_S_COMPLETE);
}