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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct export_name_res {scalar_t__ major_status; scalar_t__ minor_status; int /*<<< orphan*/  exported_name; } ;
struct export_name_args {int /*<<< orphan*/  input_name; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_1__* gss_name_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct export_name_res*,int) ; 
 int gssd_export_name_1 (struct export_name_args*,struct export_name_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgss_copy_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 
 scalar_t__ xdr_export_name_res ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct export_name_res*) ; 

OM_uint32
gss_export_name(OM_uint32 *minor_status, gss_name_t input_name,
    gss_buffer_t exported_name)
{
	struct export_name_res res;
	struct export_name_args args;
	enum clnt_stat stat;
	CLIENT *cl;

	*minor_status = 0;
	cl = kgss_gssd_client();
	if (cl == NULL)
		return (GSS_S_FAILURE);

	args.input_name = input_name->handle;

	bzero(&res, sizeof(res));
	stat = gssd_export_name_1(&args, &res, cl);
	CLNT_RELEASE(cl);
	if (stat != RPC_SUCCESS) {
		*minor_status = stat;
		return (GSS_S_FAILURE);
	}

	if (res.major_status != GSS_S_COMPLETE) {
		*minor_status = res.minor_status;
		return (res.major_status);
	}

	kgss_copy_buffer(&res.exported_name, exported_name);
	xdr_free((xdrproc_t) xdr_export_name_res, &res);

	return (GSS_S_COMPLETE);
}