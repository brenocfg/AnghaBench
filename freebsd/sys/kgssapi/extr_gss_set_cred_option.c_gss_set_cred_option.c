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
struct set_cred_option_res {scalar_t__ major_status; scalar_t__ minor_status; } ;
struct set_cred_option_args {int /*<<< orphan*/  option_value; int /*<<< orphan*/  option_name; scalar_t__ cred; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_1__* gss_cred_id_t ;
typedef  int /*<<< orphan*/ * gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_3__ {scalar_t__ handle; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct set_cred_option_res*,int) ; 
 int gssd_set_cred_option_1 (struct set_cred_option_args*,struct set_cred_option_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 

OM_uint32
gss_set_cred_option(OM_uint32 *minor_status,
	       gss_cred_id_t *cred,
	       const gss_OID option_name,
	       const gss_buffer_t option_value)
{
	struct set_cred_option_res res;
	struct set_cred_option_args args;
	enum clnt_stat stat;
	CLIENT *cl;

	*minor_status = 0;

	cl = kgss_gssd_client();
	if (cl == NULL)
		return (GSS_S_FAILURE);

	if (cred)
		args.cred = (*cred)->handle;
	else
		args.cred = 0;
	args.option_name = option_name;
	args.option_value = *option_value;

	bzero(&res, sizeof(res));
	stat = gssd_set_cred_option_1(&args, &res, cl);
	CLNT_RELEASE(cl);

	if (stat != RPC_SUCCESS) {
		*minor_status = stat;
		return (GSS_S_FAILURE);
	}

	if (res.major_status != GSS_S_COMPLETE) {
		*minor_status = res.minor_status;
		return (res.major_status);
	}

	return (GSS_S_COMPLETE);
}