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
struct TYPE_6__ {int /*<<< orphan*/  output_name; scalar_t__ major_status; scalar_t__ minor_status; } ;
typedef  TYPE_1__ canonicalize_name_res ;
struct TYPE_7__ {int /*<<< orphan*/  mech_type; int /*<<< orphan*/  input_name; } ;
typedef  TYPE_2__ canonicalize_name_args ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 scalar_t__ GSS_S_BAD_NAME ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gss_canonicalize_name (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gssd_find_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gssd_make_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gssd_verbose_out (char*,unsigned int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

bool_t
gssd_canonicalize_name_1_svc(canonicalize_name_args *argp, canonicalize_name_res *result, struct svc_req *rqstp)
{
	gss_name_t name = gssd_find_resource(argp->input_name);
	gss_name_t output_name;

	memset(result, 0, sizeof(*result));
	if (!name) {
		result->major_status = GSS_S_BAD_NAME;
		return (TRUE);
	}

	result->major_status = gss_canonicalize_name(&result->minor_status,
	    name, argp->mech_type, &output_name);
	gssd_verbose_out("gssd_canonicalize_name: done major=0x%x minor=%d\n",
	    (unsigned int)result->major_status, (int)result->minor_status);

	if (result->major_status == GSS_S_COMPLETE)
		result->output_name = gssd_make_resource(output_name);
	else
		result->output_name = 0;

	return (TRUE);
}