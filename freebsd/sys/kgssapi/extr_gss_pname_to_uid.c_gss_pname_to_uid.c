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
typedef  int /*<<< orphan*/  uid_t ;
struct pname_to_uid_res {scalar_t__ major_status; scalar_t__ minor_status; int /*<<< orphan*/  uid; } ;
struct pname_to_uid_args {int /*<<< orphan*/  mech; int /*<<< orphan*/  pname; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_1__* gss_name_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 TYPE_1__* const GSS_C_NO_NAME ; 
 scalar_t__ GSS_S_BAD_NAME ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct pname_to_uid_res*,int) ; 
 int gssd_pname_to_uid_1 (struct pname_to_uid_args*,struct pname_to_uid_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 

OM_uint32
gss_pname_to_uid(OM_uint32 *minor_status, const gss_name_t pname,
    const gss_OID mech, uid_t *uidp)
{
	struct pname_to_uid_res res;
	struct pname_to_uid_args args;
	enum clnt_stat stat;
	CLIENT *cl;

	*minor_status = 0;

	if (pname == GSS_C_NO_NAME)
		return (GSS_S_BAD_NAME);

	cl = kgss_gssd_client();
	if (cl == NULL)
		return (GSS_S_FAILURE);

	args.pname = pname->handle;
	args.mech = mech;

	bzero(&res, sizeof(res));
	stat = gssd_pname_to_uid_1(&args, &res, cl);
	CLNT_RELEASE(cl);
	if (stat != RPC_SUCCESS) {
		*minor_status = stat;
		return (GSS_S_FAILURE);
	}

	if (res.major_status != GSS_S_COMPLETE) {
		*minor_status = res.minor_status;
		return (res.major_status);
	}

	*uidp = res.uid;
	return (GSS_S_COMPLETE);
}