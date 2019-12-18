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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_5__ {int gidlist_len; int /*<<< orphan*/ * gidlist_val; } ;
struct pname_to_uid_res {scalar_t__ major_status; scalar_t__ minor_status; TYPE_1__ gidlist; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct pname_to_uid_args {int /*<<< orphan*/  mech; int /*<<< orphan*/  pname; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_2__* gss_name_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 TYPE_2__* const GSS_C_NO_NAME ; 
 scalar_t__ GSS_S_BAD_NAME ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct pname_to_uid_res*,int) ; 
 int gssd_pname_to_uid_1 (struct pname_to_uid_args*,struct pname_to_uid_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct pname_to_uid_res*) ; 
 scalar_t__ xdr_pname_to_uid_res ; 

OM_uint32
gss_pname_to_unix_cred(OM_uint32 *minor_status, const gss_name_t pname,
    const gss_OID mech, uid_t *uidp, gid_t *gidp,
    int *numgroups, gid_t *groups)
	      
{
	struct pname_to_uid_res res;
	struct pname_to_uid_args args;
	enum clnt_stat stat;
	int i, n;
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
	*gidp = res.gid;
	n = res.gidlist.gidlist_len;
	if (n > *numgroups)
		n = *numgroups;
	for (i = 0; i < n; i++)
		groups[i] = res.gidlist.gidlist_val[i];
	*numgroups = n;

	xdr_free((xdrproc_t) xdr_pname_to_uid_res, &res);

	return (GSS_S_COMPLETE);
}