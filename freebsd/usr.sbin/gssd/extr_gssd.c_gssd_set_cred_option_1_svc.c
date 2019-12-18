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
struct TYPE_6__ {scalar_t__ minor_status; scalar_t__ major_status; } ;
typedef  TYPE_1__ set_cred_option_res ;
struct TYPE_7__ {int /*<<< orphan*/  option_value; int /*<<< orphan*/  option_name; int /*<<< orphan*/  cred; } ;
typedef  TYPE_2__ set_cred_option_args ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 scalar_t__ GSS_S_CREDENTIALS_EXPIRED ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gss_set_cred_option (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gssd_find_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gssd_verbose_out (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

bool_t
gssd_set_cred_option_1_svc(set_cred_option_args *argp, set_cred_option_res *result, struct svc_req *rqstp)
{
	gss_cred_id_t cred = gssd_find_resource(argp->cred);

	memset(result, 0, sizeof(*result));
	if (!cred) {
		result->major_status = GSS_S_CREDENTIALS_EXPIRED;
		gssd_verbose_out("gssd_set_cred: no credentials\n");
		return (TRUE);
	}

	result->major_status = gss_set_cred_option(&result->minor_status,
	    &cred, argp->option_name, &argp->option_value);
	gssd_verbose_out("gssd_set_cred: done major=0x%x minor=%d\n",
	    (unsigned int)result->major_status, (int)result->minor_status);

	return (TRUE);
}