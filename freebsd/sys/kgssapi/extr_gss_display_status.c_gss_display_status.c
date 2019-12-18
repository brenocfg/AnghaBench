#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct display_status_res {scalar_t__ major_status; scalar_t__ minor_status; scalar_t__ message_context; int /*<<< orphan*/  status_string; } ;
struct display_status_args {int status_type; scalar_t__ message_context; int /*<<< orphan*/  mech_type; scalar_t__ status_value; } ;
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct display_status_res*,int) ; 
 int gssd_display_status_1 (struct display_status_args*,struct display_status_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgss_copy_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 
 scalar_t__ xdr_display_status_res ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct display_status_res*) ; 

OM_uint32
gss_display_status(OM_uint32 *minor_status,
    OM_uint32 status_value,
    int status_type,
    const gss_OID mech_type,
    OM_uint32 *message_context,
    gss_buffer_t status_string)            /* status_string */
{
	struct display_status_res res;
	struct display_status_args args;
	enum clnt_stat stat;
	CLIENT *cl;

	*minor_status = 0;
	cl = kgss_gssd_client();
	if (cl == NULL)
		return (GSS_S_FAILURE);

	args.status_value = status_value;
	args.status_type = status_type;
	args.mech_type = mech_type;
	args.message_context = *message_context;
	
	bzero(&res, sizeof(res));
	stat = gssd_display_status_1(&args, &res, cl);
	CLNT_RELEASE(cl);
	if (stat != RPC_SUCCESS) {
		*minor_status = stat;
		return (GSS_S_FAILURE);
	}

	if (res.major_status != GSS_S_COMPLETE) {
		*minor_status = res.minor_status;
		return (res.major_status);
	}

	*message_context = res.message_context;
	kgss_copy_buffer(&res.status_string, status_string);
	xdr_free((xdrproc_t) xdr_display_status_res, &res);

	return (GSS_S_COMPLETE);
}