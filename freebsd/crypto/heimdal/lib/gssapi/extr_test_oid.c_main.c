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
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NT_EXPORT_NAME ; 
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  gss_oid_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
    OM_uint32 minor_status, maj_stat;
    gss_buffer_desc data;
    int ret;

    maj_stat = gss_oid_to_str(&minor_status, GSS_KRB5_MECHANISM, &data);
    if (GSS_ERROR(maj_stat))
	errx(1, "gss_oid_to_str failed");

    ret = strncmp(data.value, "1 2 840 113554 1 2 2", data.length);
    gss_release_buffer(&maj_stat, &data);
    if (ret)
	return 1;

    maj_stat = gss_oid_to_str(&minor_status, GSS_C_NT_EXPORT_NAME, &data);
    if (GSS_ERROR(maj_stat))
	errx(1, "gss_oid_to_str failed");

    ret = strncmp(data.value, "1 3 6 1 5 6 4", data.length);
    gss_release_buffer(&maj_stat, &data);
    if (ret)
	return 1;

    return 0;
}