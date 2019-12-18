#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_OID_set ;
struct TYPE_7__ {size_t count; int /*<<< orphan*/ * elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_SPNEGO_MECHANISM ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ gss_add_oid_set_member (scalar_t__*,int /*<<< orphan*/ *,TYPE_1__**) ; 
 scalar_t__ gss_create_empty_oid_set (scalar_t__*,TYPE_1__**) ; 
 scalar_t__ gss_indicate_mechs (scalar_t__*,TYPE_1__**) ; 
 scalar_t__ gss_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_release_oid_set (scalar_t__*,TYPE_1__**) ; 

__attribute__((used)) static OM_uint32
spnego_supported_mechs(OM_uint32 *minor_status, gss_OID_set *mechs)
{
    OM_uint32 ret, junk;
    gss_OID_set m;
    size_t i;

    ret = gss_indicate_mechs(minor_status, &m);
    if (ret != GSS_S_COMPLETE)
	return ret;

    ret = gss_create_empty_oid_set(minor_status, mechs);
    if (ret != GSS_S_COMPLETE) {
	gss_release_oid_set(&junk, &m);
	return ret;
    }

    for (i = 0; i < m->count; i++) {
	if (gss_oid_equal(&m->elements[i], GSS_SPNEGO_MECHANISM))
	    continue;

	ret = gss_add_oid_set_member(minor_status, &m->elements[i], mechs);
	if (ret) {
	    gss_release_oid_set(&junk, &m);
	    gss_release_oid_set(&junk, mechs);
	    return ret;
	}
    }
    gss_release_oid_set(&junk, &m);
    return ret;
}