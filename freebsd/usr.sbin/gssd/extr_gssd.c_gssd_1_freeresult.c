#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ xdrproc_t ;
struct TYPE_12__ {scalar_t__ gidlist_val; } ;
struct TYPE_13__ {TYPE_1__ gidlist; } ;
typedef  TYPE_2__ pname_to_uid_res ;
struct TYPE_11__ {scalar_t__ length; int /*<<< orphan*/  value; } ;
struct TYPE_14__ {TYPE_10__ output_token; } ;
typedef  TYPE_3__ init_sec_context_res ;
struct TYPE_15__ {TYPE_10__ interprocess_token; } ;
typedef  TYPE_4__ export_sec_context_res ;
struct TYPE_16__ {TYPE_10__ exported_name; } ;
typedef  TYPE_5__ export_name_res ;
struct TYPE_17__ {TYPE_10__ status_string; } ;
typedef  TYPE_6__ display_status_res ;
struct TYPE_18__ {TYPE_10__ output_token; } ;
typedef  TYPE_7__ delete_sec_context_res ;
typedef  scalar_t__ caddr_t ;
struct TYPE_19__ {int /*<<< orphan*/  actual_mechs; } ;
typedef  TYPE_8__ acquire_cred_res ;
struct TYPE_20__ {TYPE_10__ output_token; } ;
typedef  TYPE_9__ accept_sec_context_res ;
typedef  int /*<<< orphan*/  SVCXPRT ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  gss_release_oid_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ xdr_accept_sec_context_res ; 
 scalar_t__ xdr_acquire_cred_res ; 
 scalar_t__ xdr_delete_sec_context_res ; 
 scalar_t__ xdr_display_status_res ; 
 scalar_t__ xdr_export_name_res ; 
 scalar_t__ xdr_export_sec_context_res ; 
 scalar_t__ xdr_init_sec_context_res ; 
 scalar_t__ xdr_pname_to_uid_res ; 

int
gssd_1_freeresult(SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	/*
	 * We don't use XDR to free the results - anything which was
	 * allocated came from GSS-API. We use xdr_result to figure
	 * out what to do.
	 */
	OM_uint32 junk;

	if (xdr_result == (xdrproc_t) xdr_init_sec_context_res) {
		init_sec_context_res *p = (init_sec_context_res *) result;
		gss_release_buffer(&junk, &p->output_token);
	} else if (xdr_result == (xdrproc_t) xdr_accept_sec_context_res) {
		accept_sec_context_res *p = (accept_sec_context_res *) result;
		gss_release_buffer(&junk, &p->output_token);
	} else if (xdr_result == (xdrproc_t) xdr_delete_sec_context_res) {
		delete_sec_context_res *p = (delete_sec_context_res *) result;
		gss_release_buffer(&junk, &p->output_token);
	} else if (xdr_result == (xdrproc_t) xdr_export_sec_context_res) {
		export_sec_context_res *p = (export_sec_context_res *) result;
		if (p->interprocess_token.length)
			memset(p->interprocess_token.value, 0,
			    p->interprocess_token.length);
		gss_release_buffer(&junk, &p->interprocess_token);
	} else if (xdr_result == (xdrproc_t) xdr_export_name_res) {
		export_name_res *p = (export_name_res *) result;
		gss_release_buffer(&junk, &p->exported_name);
	} else if (xdr_result == (xdrproc_t) xdr_acquire_cred_res) {
		acquire_cred_res *p = (acquire_cred_res *) result;
		gss_release_oid_set(&junk, &p->actual_mechs);
	} else if (xdr_result == (xdrproc_t) xdr_pname_to_uid_res) {
		pname_to_uid_res *p = (pname_to_uid_res *) result;
		if (p->gidlist.gidlist_val)
			free(p->gidlist.gidlist_val);
	} else if (xdr_result == (xdrproc_t) xdr_display_status_res) {
		display_status_res *p = (display_status_res *) result;
		gss_release_buffer(&junk, &p->status_string);
	}

	return (TRUE);
}