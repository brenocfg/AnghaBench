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
typedef  scalar_t__ gss_name_t ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID_set ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_C_NO_NAME ; 
 int /*<<< orphan*/  GSS_C_NO_OID ; 
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  gss_acquire_cred (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_import_name (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gss_release_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_name (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  gssapi_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_UNCONST (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gss_cred_id_t
acquire_cred_service(const char *service,
		     gss_OID nametype,
		     gss_OID_set oidset,
		     int flags)
{
    OM_uint32 major_status, minor_status;
    gss_cred_id_t cred_handle;
    OM_uint32 time_rec;
    gss_buffer_desc name_buffer;
    gss_name_t name = GSS_C_NO_NAME;

    if (service) {
	name_buffer.value = rk_UNCONST(service);
	name_buffer.length = strlen(service);

	major_status = gss_import_name(&minor_status,
				       &name_buffer,
				       nametype,
				       &name);
	if (GSS_ERROR(major_status))
	    errx(1, "import_name failed");
    }

    major_status = gss_acquire_cred(&minor_status,
				    name,
				    0,
				    oidset,
				    flags,
				    &cred_handle,
				    NULL,
				    &time_rec);
    if (GSS_ERROR(major_status)) {
	warnx("acquire_cred failed: %s",
	     gssapi_err(major_status, minor_status, GSS_C_NO_OID));
    } else {
	print_time(time_rec);
	gss_release_cred(&minor_status, &cred_handle);
    }

    if (name != GSS_C_NO_NAME)
	gss_release_name(&minor_status, &name);

    if (GSS_ERROR(major_status))
	exit(1);

    return cred_handle;
}