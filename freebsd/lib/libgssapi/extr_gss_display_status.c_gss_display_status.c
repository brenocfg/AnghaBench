#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_9__ {int length; scalar_t__ value; } ;
typedef  TYPE_2__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_8__ {char* value; void* length; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_CALLING_ERROR (scalar_t__) ; 
#define  GSS_C_GSS_CODE 129 
#define  GSS_C_MECH_CODE 128 
 int /*<<< orphan*/  GSS_ROUTINE_ERROR (scalar_t__) ; 
 int /*<<< orphan*/  GSS_SUPPLEMENTARY_INFO (scalar_t__) ; 
 scalar_t__ GSS_S_BAD_STATUS ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  _gss_buffer_zero (TYPE_1__*) ; 
 scalar_t__ _gss_mg_get_error (int /*<<< orphan*/  const,int,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  asprintf (char**,char*,unsigned long,...) ; 
 int /*<<< orphan*/  calling_error (int /*<<< orphan*/ ) ; 
 scalar_t__ gss_oid_to_str (scalar_t__*,int /*<<< orphan*/  const,TYPE_2__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_2__*) ; 
 int /*<<< orphan*/  routine_error (int /*<<< orphan*/ ) ; 
 scalar_t__ strdup (char*) ; 
 void* strlen (char*) ; 
 int /*<<< orphan*/  supplementary_error (int /*<<< orphan*/ ) ; 

OM_uint32
gss_display_status(OM_uint32 *minor_status,
    OM_uint32 status_value,
    int status_type,
    const gss_OID mech_type,
    OM_uint32 *message_content,
    gss_buffer_t status_string)
{
	OM_uint32 major_status;

	_gss_buffer_zero(status_string);
	*message_content = 0;

	major_status = _gss_mg_get_error(mech_type, status_type,
					 status_value, status_string);
	if (major_status == GSS_S_COMPLETE) {

		*message_content = 0;
		*minor_status = 0;
		return (GSS_S_COMPLETE);
	}

	*minor_status = 0;
	switch (status_type) {
	case GSS_C_GSS_CODE: {
		char *buf;

		if (GSS_SUPPLEMENTARY_INFO(status_value))
		    asprintf(&buf, "%s", supplementary_error(
		        GSS_SUPPLEMENTARY_INFO(status_value)));
		else
		    asprintf (&buf, "%s %s",
		        calling_error(GSS_CALLING_ERROR(status_value)),
			routine_error(GSS_ROUTINE_ERROR(status_value)));

		if (buf == NULL)
			break;

		status_string->length = strlen(buf);
		status_string->value  = buf;

		return (GSS_S_COMPLETE);
	}
	case GSS_C_MECH_CODE: {
		OM_uint32 maj_junk, min_junk;
		gss_buffer_desc oid;
		char *buf;

		maj_junk = gss_oid_to_str(&min_junk, mech_type, &oid);
		if (maj_junk != GSS_S_COMPLETE) {
			oid.value = strdup("unknown");
			oid.length = 7;
		}

		asprintf (&buf, "unknown mech-code %lu for mech %.*s",
			  (unsigned long)status_value,
			  (int)oid.length, (char *)oid.value);
		if (maj_junk == GSS_S_COMPLETE)
			gss_release_buffer(&min_junk, &oid);

		if (buf == NULL)
		    break;

		status_string->length = strlen(buf);
		status_string->value  = buf;

		return (GSS_S_COMPLETE);
	}
	}
	_gss_buffer_zero(status_string);
	return (GSS_S_BAD_STATUS);
}