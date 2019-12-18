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
struct _gss_mech_switch {scalar_t__ (* gm_inquire_names_for_mech ) (scalar_t__*,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  gss_OID_set ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_OID_SET ; 
 int /*<<< orphan*/  GSS_C_NT_HOSTBASED_SERVICE ; 
 int /*<<< orphan*/  GSS_C_NT_USER_NAME ; 
 scalar_t__ GSS_S_BAD_MECH ; 
 scalar_t__ GSS_S_COMPLETE ; 
 struct _gss_mech_switch* _gss_find_mech_switch (int /*<<< orphan*/  const) ; 
 scalar_t__ gss_add_oid_set_member (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_create_empty_oid_set (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_oid_set (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (scalar_t__*,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

OM_uint32
gss_inquire_names_for_mech(OM_uint32 *minor_status,
    const gss_OID mechanism,
    gss_OID_set *name_types)
{
	OM_uint32 major_status;
	struct _gss_mech_switch *m = _gss_find_mech_switch(mechanism);

	*minor_status = 0;
	*name_types = GSS_C_NO_OID_SET;
	if (!m)
		return (GSS_S_BAD_MECH);

	/*
	 * If the implementation can do it, ask it for a list of
	 * names, otherwise fake it.
	 */
	if (m->gm_inquire_names_for_mech) {
		return (m->gm_inquire_names_for_mech(minor_status,
			    mechanism, name_types));
	} else {
		major_status = gss_create_empty_oid_set(minor_status,
		    name_types);
		if (major_status)
			return (major_status);
		major_status = gss_add_oid_set_member(minor_status,
		    GSS_C_NT_HOSTBASED_SERVICE, name_types);
		if (major_status) {
			OM_uint32 junk;
			gss_release_oid_set(&junk, name_types);
			return (major_status);
		}
		major_status = gss_add_oid_set_member(minor_status,
		    GSS_C_NT_USER_NAME, name_types);
		if (major_status) {
			OM_uint32 junk;
			gss_release_oid_set(&junk, name_types);
			return (major_status);
		}
	}

	return (GSS_S_COMPLETE);
}