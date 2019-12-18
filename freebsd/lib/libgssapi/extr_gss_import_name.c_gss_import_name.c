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
struct _gss_name {int /*<<< orphan*/  gn_mn; int /*<<< orphan*/  gn_value; int /*<<< orphan*/  gn_type; } ;
typedef  scalar_t__ gss_name_t ;
typedef  TYPE_1__* gss_buffer_t ;
typedef  scalar_t__ gss_OID ;
struct TYPE_5__ {scalar_t__ length; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ GSS_C_NO_NAME ; 
 scalar_t__ GSS_C_NO_OID ; 
 scalar_t__ GSS_C_NT_ANONYMOUS ; 
 scalar_t__ GSS_C_NT_EXPORT_NAME ; 
 scalar_t__ GSS_C_NT_HOSTBASED_SERVICE ; 
 scalar_t__ GSS_C_NT_HOSTBASED_SERVICE_X ; 
 scalar_t__ GSS_C_NT_MACHINE_UID_NAME ; 
 scalar_t__ GSS_C_NT_STRING_UID_NAME ; 
 scalar_t__ GSS_C_NT_USER_NAME ; 
 scalar_t__ GSS_KRB5_NT_PRINCIPAL_NAME ; 
 scalar_t__ GSS_S_BAD_NAME ; 
 scalar_t__ GSS_S_BAD_NAMETYPE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ _gss_copy_buffer (scalar_t__*,TYPE_1__* const,int /*<<< orphan*/ *) ; 
 scalar_t__ _gss_copy_oid (scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ _gss_import_export_name (scalar_t__*,TYPE_1__* const,scalar_t__*) ; 
 int /*<<< orphan*/  free (struct _gss_name*) ; 
 scalar_t__ gss_oid_equal (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gss_release_name (scalar_t__*,scalar_t__*) ; 
 struct _gss_name* malloc (int) ; 
 int /*<<< orphan*/  memset (struct _gss_name*,int /*<<< orphan*/ ,int) ; 

OM_uint32
gss_import_name(OM_uint32 *minor_status,
    const gss_buffer_t input_name_buffer,
    const gss_OID input_name_type,
    gss_name_t *output_name)
{
	gss_OID			name_type = input_name_type;
	OM_uint32		major_status;
	struct _gss_name	*name;

	*output_name = GSS_C_NO_NAME;

	if (input_name_buffer->length == 0) {
		*minor_status = 0;
		return (GSS_S_BAD_NAME);
	}

	/*
	 * Use GSS_NT_USER_NAME as default name type.
	 */
	if (name_type == GSS_C_NO_OID)
		name_type = GSS_C_NT_USER_NAME;

	/*
	 * If this is an exported name, we need to parse it to find
	 * the mechanism and then import it as an MN. See RFC 2743
	 * section 3.2 for a description of the format.
	 */
	if (gss_oid_equal(name_type, GSS_C_NT_EXPORT_NAME)) {
		return _gss_import_export_name(minor_status,
		    input_name_buffer, output_name);
	}

	/*
	 * Only allow certain name types. This is pretty bogus - we
	 * should figure out the list of supported name types using
	 * gss_inquire_names_for_mech.
	 */
	if (!gss_oid_equal(name_type, GSS_C_NT_USER_NAME)
	    && !gss_oid_equal(name_type, GSS_C_NT_MACHINE_UID_NAME)
	    && !gss_oid_equal(name_type, GSS_C_NT_STRING_UID_NAME)
	    && !gss_oid_equal(name_type, GSS_C_NT_HOSTBASED_SERVICE_X)
	    && !gss_oid_equal(name_type, GSS_C_NT_HOSTBASED_SERVICE)
	    && !gss_oid_equal(name_type, GSS_C_NT_ANONYMOUS)
	    && !gss_oid_equal(name_type, GSS_KRB5_NT_PRINCIPAL_NAME)) {
		*minor_status = 0;
		return (GSS_S_BAD_NAMETYPE);
	}

	*minor_status = 0;
	name = malloc(sizeof(struct _gss_name));
	if (!name) {
		*minor_status = ENOMEM;
		return (GSS_S_FAILURE);
	}
	memset(name, 0, sizeof(struct _gss_name));

	major_status = _gss_copy_oid(minor_status,
	    name_type, &name->gn_type);
	if (major_status) {
		free(name);
		return (GSS_S_FAILURE);
	}

	major_status = _gss_copy_buffer(minor_status,
	    input_name_buffer, &name->gn_value);
	if (major_status) {
		gss_name_t rname = (gss_name_t)name;
		gss_release_name(minor_status, &rname);
		return (GSS_S_FAILURE);
	}

	SLIST_INIT(&name->gn_mn);

	*output_name = (gss_name_t) name;
	return (GSS_S_COMPLETE);
}