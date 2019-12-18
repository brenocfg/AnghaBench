#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct canonicalize_name_res {scalar_t__ major_status; scalar_t__ minor_status; int /*<<< orphan*/  output_name; } ;
struct canonicalize_name_args {int /*<<< orphan*/  mech_type; int /*<<< orphan*/  input_name; } ;
struct _gss_name_t {int dummy; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_1__* gss_name_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct canonicalize_name_res*,int) ; 
 int gssd_canonicalize_name_1 (struct canonicalize_name_args*,struct canonicalize_name_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OM_uint32
gss_canonicalize_name(OM_uint32 *minor_status,
    gss_name_t input_name,
    const gss_OID mech_type,
    gss_name_t *output_name)
{
	struct canonicalize_name_res res;
	struct canonicalize_name_args args;
	enum clnt_stat stat;
	gss_name_t name;
	CLIENT *cl;

	*minor_status = 0;
	cl = kgss_gssd_client();
	if (cl == NULL)
		return (GSS_S_FAILURE);

	args.input_name = input_name->handle;
	args.mech_type = mech_type;
	
	bzero(&res, sizeof(res));
	stat = gssd_canonicalize_name_1(&args, &res, cl);
	CLNT_RELEASE(cl);
	if (stat != RPC_SUCCESS) {
		*minor_status = stat;
		return (GSS_S_FAILURE);
	}

	if (res.major_status != GSS_S_COMPLETE) {
		*minor_status = res.minor_status;
		return (res.major_status);
	}

	name = malloc(sizeof(struct _gss_name_t), M_GSSAPI, M_WAITOK);
	name->handle = res.output_name;
	*output_name = name;

	return (GSS_S_COMPLETE);
}