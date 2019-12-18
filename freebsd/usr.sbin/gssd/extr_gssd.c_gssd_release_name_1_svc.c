#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_5__ {scalar_t__ minor_status; scalar_t__ major_status; } ;
typedef  TYPE_1__ release_name_res ;
struct TYPE_6__ {int /*<<< orphan*/  input_name; } ;
typedef  TYPE_2__ release_name_args ;
typedef  scalar_t__ gss_name_t ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gss_release_name (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gssd_delete_resource (int /*<<< orphan*/ ) ; 
 scalar_t__ gssd_find_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gssd_verbose_out (char*,unsigned int,int) ; 

bool_t
gssd_release_name_1_svc(release_name_args *argp, release_name_res *result, struct svc_req *rqstp)
{
	gss_name_t name = gssd_find_resource(argp->input_name);

	if (name) {
		result->major_status = gss_release_name(&result->minor_status,
		    &name);
		gssd_delete_resource(argp->input_name);
	} else {
		result->major_status = GSS_S_COMPLETE;
		result->minor_status = 0;
	}
	gssd_verbose_out("gssd_release_name: done major=0x%x minor=%d\n",
	    (unsigned int)result->major_status, (int)result->minor_status);

	return (TRUE);
}