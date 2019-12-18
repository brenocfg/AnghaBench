#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ value; scalar_t__ length; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  scalar_t__ gss_OID ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_GSS_CODE ; 
 int /*<<< orphan*/  GSS_C_MECH_CODE ; 
 scalar_t__ GSS_C_NO_OID ; 
 scalar_t__ GSS_ERROR (scalar_t__) ; 
 scalar_t__ gss_display_status (scalar_t__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uprintf (char*,int,char*) ; 

__attribute__((used)) static void
report_error(gss_OID mech, OM_uint32 maj, OM_uint32 min)
{
	OM_uint32 maj_stat, min_stat;
	OM_uint32 message_context;
	gss_buffer_desc buf;

	uprintf("major_stat=%d, minor_stat=%d\n", maj, min);
	message_context = 0;
	do {
		maj_stat = gss_display_status(&min_stat, maj,
		    GSS_C_GSS_CODE, GSS_C_NO_OID, &message_context, &buf);
		if (GSS_ERROR(maj_stat))
			break;
		uprintf("%.*s\n", (int)buf.length, (char *) buf.value);
		gss_release_buffer(&min_stat, &buf);
	} while (message_context);
	if (mech && min) {
		message_context = 0;
		do {
			maj_stat = gss_display_status(&min_stat, min,
			    GSS_C_MECH_CODE, mech, &message_context, &buf);
			if (GSS_ERROR(maj_stat))
				break;
			uprintf("%.*s\n", (int)buf.length, (char *) buf.value);
			gss_release_buffer(&min_stat, &buf);
		} while (message_context);
	}
}