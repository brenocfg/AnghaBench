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
typedef  TYPE_1__* gss_OID_set ;
struct TYPE_5__ {struct TYPE_5__* elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 TYPE_1__* GSS_C_NO_OID_SET ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 

OM_uint32
gss_release_oid_set(OM_uint32 *minor_status,
    gss_OID_set *set)
{

	*minor_status = 0;
	if (set && *set) {
		if ((*set)->elements)
			free((*set)->elements, M_GSSAPI);
		free(*set, M_GSSAPI);
		*set = GSS_C_NO_OID_SET;
	}
	return (GSS_S_COMPLETE);
}