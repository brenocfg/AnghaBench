#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct acquire_cred_res {scalar_t__ major_status; scalar_t__ minor_status; scalar_t__ time_rec; TYPE_2__* actual_mechs; int /*<<< orphan*/  output_cred; } ;
struct acquire_cred_args {int /*<<< orphan*/  cred_usage; int /*<<< orphan*/  desired_mechs; scalar_t__ time_req; scalar_t__ desired_name; int /*<<< orphan*/  uid; } ;
struct _gss_cred_id_t {int dummy; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_3__* gss_name_t ;
typedef  int /*<<< orphan*/  gss_cred_usage_t ;
typedef  TYPE_4__* gss_cred_id_t ;
typedef  int /*<<< orphan*/  gss_OID_set ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_13__ {TYPE_1__* td_ucred; } ;
struct TYPE_12__ {int /*<<< orphan*/  handle; } ;
struct TYPE_11__ {scalar_t__ handle; } ;
struct TYPE_10__ {int count; int /*<<< orphan*/ * elements; } ;
struct TYPE_9__ {int /*<<< orphan*/  cr_uid; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct acquire_cred_res*,int) ; 
 TYPE_8__* curthread ; 
 scalar_t__ gss_add_oid_set_member (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_create_empty_oid_set (scalar_t__*,int /*<<< orphan*/ *) ; 
 int gssd_acquire_cred_1 (struct acquire_cred_args*,struct acquire_cred_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 
 TYPE_4__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_acquire_cred_res ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct acquire_cred_res*) ; 

OM_uint32
gss_acquire_cred(OM_uint32 *minor_status,
    const gss_name_t desired_name,
    OM_uint32 time_req,
    const gss_OID_set desired_mechs,
    gss_cred_usage_t cred_usage,
    gss_cred_id_t *output_cred_handle,
    gss_OID_set *actual_mechs,
    OM_uint32 *time_rec)
{
	OM_uint32 major_status;
	struct acquire_cred_res res;
	struct acquire_cred_args args;
	enum clnt_stat stat;
	gss_cred_id_t cred;
	int i;
	CLIENT *cl;

	*minor_status = 0;
	cl = kgss_gssd_client();
	if (cl == NULL)
		return (GSS_S_FAILURE);

	args.uid = curthread->td_ucred->cr_uid;
	if (desired_name)
		args.desired_name = desired_name->handle;
	else
		args.desired_name = 0;
	args.time_req = time_req;
	args.desired_mechs = desired_mechs;
	args.cred_usage = cred_usage;

	bzero(&res, sizeof(res));
	stat = gssd_acquire_cred_1(&args, &res, cl);
	CLNT_RELEASE(cl);
	if (stat != RPC_SUCCESS) {
		*minor_status = stat;
		return (GSS_S_FAILURE);
	}

	if (res.major_status != GSS_S_COMPLETE) {
		*minor_status = res.minor_status;
		return (res.major_status);
	}

	cred = malloc(sizeof(struct _gss_cred_id_t), M_GSSAPI, M_WAITOK);
	cred->handle = res.output_cred;
	*output_cred_handle = cred;
	if (actual_mechs) {
		major_status = gss_create_empty_oid_set(minor_status,
		    actual_mechs);
		if (major_status)
			return (major_status);
		for (i = 0; i < res.actual_mechs->count; i++) {
			major_status = gss_add_oid_set_member(minor_status,
			    &res.actual_mechs->elements[i], actual_mechs);
			if (major_status)
				return (major_status);
		}
	}
	if (time_rec)
		*time_rec = res.time_rec;

	xdr_free((xdrproc_t) xdr_acquire_cred_res, &res);

	return (GSS_S_COMPLETE);
}