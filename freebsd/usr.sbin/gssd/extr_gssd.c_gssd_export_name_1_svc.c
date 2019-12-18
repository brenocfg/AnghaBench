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
struct svc_req {int dummy; } ;
typedef  int /*<<< orphan*/  gss_name_t ;
struct TYPE_6__ {scalar_t__ minor_status; scalar_t__ major_status; int /*<<< orphan*/  exported_name; } ;
typedef  TYPE_1__ export_name_res ;
struct TYPE_7__ {int /*<<< orphan*/  input_name; } ;
typedef  TYPE_2__ export_name_args ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 scalar_t__ GSS_S_BAD_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gss_export_name (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gssd_find_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gssd_verbose_out (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

bool_t
gssd_export_name_1_svc(export_name_args *argp, export_name_res *result, struct svc_req *rqstp)
{
	gss_name_t name = gssd_find_resource(argp->input_name);

	memset(result, 0, sizeof(*result));
	if (!name) {
		result->major_status = GSS_S_BAD_NAME;
		gssd_verbose_out("gssd_export_name: name resource not found\n");
		return (TRUE);
	}

	result->major_status = gss_export_name(&result->minor_status,
	    name, &result->exported_name);
	gssd_verbose_out("gssd_export_name: done major=0x%x minor=%d\n",
	    (unsigned int)result->major_status, (int)result->minor_status);

	return (TRUE);
}