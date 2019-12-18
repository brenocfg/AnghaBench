#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct _gss_name {int dummy; } ;
struct _gss_mech_switch {scalar_t__ (* gm_import_name ) (scalar_t__*,TYPE_1__* const,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  (* gm_release_name ) (scalar_t__*,scalar_t__*) ;} ;
typedef  scalar_t__ gss_name_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_7__ {int length; unsigned char* elements; } ;
typedef  TYPE_2__ gss_OID_desc ;
struct TYPE_6__ {unsigned char* value; size_t length; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NT_EXPORT_NAME ; 
 scalar_t__ GSS_S_BAD_MECH ; 
 scalar_t__ GSS_S_BAD_NAME ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 struct _gss_mech_switch* _gss_find_mech_switch (TYPE_2__*) ; 
 struct _gss_name* _gss_make_name (struct _gss_mech_switch*,scalar_t__) ; 
 int /*<<< orphan*/  _gss_mg_error (struct _gss_mech_switch*,scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__*,TYPE_1__* const,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static OM_uint32
_gss_import_export_name(OM_uint32 *minor_status,
    const gss_buffer_t input_name_buffer,
    gss_name_t *output_name)
{
	OM_uint32 major_status;
	unsigned char *p = input_name_buffer->value;
	size_t len = input_name_buffer->length;
	size_t t;
	gss_OID_desc mech_oid;
	struct _gss_mech_switch *m;
	struct _gss_name *name;
	gss_name_t new_canonical_name;

	*minor_status = 0;
	*output_name = 0;

	/*
	 * Make sure that TOK_ID is {4, 1}.
	 */
	if (len < 2)
		return (GSS_S_BAD_NAME);
	if (p[0] != 4 || p[1] != 1)
		return (GSS_S_BAD_NAME);
	p += 2;
	len -= 2;

	/*
	 * Get the mech length and the name length and sanity
	 * check the size of of the buffer.
	 */
	if (len < 2)
		return (GSS_S_BAD_NAME);
	t = (p[0] << 8) + p[1];
	p += 2;
	len -= 2;

	/*
	 * Check the DER encoded OID to make sure it agrees with the
	 * length we just decoded.
	 */
	if (p[0] != 6)		/* 6=OID */
		return (GSS_S_BAD_NAME);
	p++;
	len--;
	t--;
	if (p[0] & 0x80) {
		int digits = p[0];
		p++;
		len--;
		t--;
		mech_oid.length = 0;
		while (digits--) {
			mech_oid.length = (mech_oid.length << 8) | p[0];
			p++;
			len--;
			t--;
		}
	} else {
		mech_oid.length = p[0];
		p++;
		len--;
		t--;
	}
	if (mech_oid.length != t)
		return (GSS_S_BAD_NAME);

	mech_oid.elements = p;

	if (len < t + 4)
		return (GSS_S_BAD_NAME);
	p += t;
	len -= t;

	t = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	p += 4;
	len -= 4;

	if (len != t)
		return (GSS_S_BAD_NAME);

	m = _gss_find_mech_switch(&mech_oid);
	if (!m)
		return (GSS_S_BAD_MECH);

	/*
	 * Ask the mechanism to import the name.
	 */
	major_status = m->gm_import_name(minor_status,
	    input_name_buffer, GSS_C_NT_EXPORT_NAME, &new_canonical_name);
	if (major_status != GSS_S_COMPLETE) {
		_gss_mg_error(m, major_status, *minor_status);
		return (major_status);
	}

	/*
	 * Now we make a new name and mark it as an MN.
	 */
	name = _gss_make_name(m, new_canonical_name);
	if (!name) {
		m->gm_release_name(minor_status, &new_canonical_name);
		return (GSS_S_FAILURE);
	}

	*output_name = (gss_name_t) name;

	*minor_status = 0;
	return (GSS_S_COMPLETE);
}