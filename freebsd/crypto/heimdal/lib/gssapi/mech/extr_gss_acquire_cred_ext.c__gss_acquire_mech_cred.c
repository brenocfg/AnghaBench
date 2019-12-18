#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct _gss_mechanism_name {int /*<<< orphan*/  gmn_name; } ;
struct _gss_mechanism_cred {int /*<<< orphan*/  gmc_cred; int /*<<< orphan*/ * gmc_mech_oid; TYPE_2__* gmc_mech; } ;
typedef  TYPE_2__* gssapi_mech_interface ;
typedef  int /*<<< orphan*/  gss_cred_usage_t ;
typedef  scalar_t__ gss_const_OID ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
struct TYPE_9__ {int count; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_3__ gss_OID_set_desc ;
struct TYPE_8__ {int /*<<< orphan*/  (* gm_acquire_cred ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_1__* gm_compat; int /*<<< orphan*/  (* gm_acquire_cred_ext ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  gm_mech_oid; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* gmc_acquire_cred_with_password ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GSS_C_CRED_PASSWORD ; 
 scalar_t__ GSS_C_NO_OID ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int /*<<< orphan*/  GSS_S_UNAVAILABLE ; 
 struct _gss_mechanism_cred* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct _gss_mechanism_cred*) ; 
 scalar_t__ gss_oid_equal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

OM_uint32
_gss_acquire_mech_cred(OM_uint32 *minor_status,
		       gssapi_mech_interface m,
		       const struct _gss_mechanism_name *mn,
		       gss_const_OID credential_type,
		       const void *credential_data,
		       OM_uint32 time_req,
		       gss_const_OID desired_mech,
		       gss_cred_usage_t cred_usage,
		       struct _gss_mechanism_cred **output_cred_handle)
{
    OM_uint32 major_status;
    struct _gss_mechanism_cred *mc;
    gss_OID_set_desc set2;

    *output_cred_handle = NULL;

    mc = calloc(1, sizeof(struct _gss_mechanism_cred));
    if (mc == NULL) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    mc->gmc_mech = m;
    mc->gmc_mech_oid = &m->gm_mech_oid;

    set2.count = 1;
    set2.elements = mc->gmc_mech_oid;

    if (m->gm_acquire_cred_ext) {
	major_status = m->gm_acquire_cred_ext(minor_status,
					      mn->gmn_name,
					      credential_type,
					      credential_data,
					      time_req,
					      mc->gmc_mech_oid,
					      cred_usage,
					      &mc->gmc_cred);
    } else if (gss_oid_equal(credential_type, GSS_C_CRED_PASSWORD) &&
		m->gm_compat &&
		m->gm_compat->gmc_acquire_cred_with_password) {
	/*
	 * Shim for mechanisms that adhere to API-as-SPI and do not
	 * implement gss_acquire_cred_ext().
	 */

	major_status = m->gm_compat->gmc_acquire_cred_with_password(minor_status,
				mn->gmn_name,
				(const gss_buffer_t)credential_data,
				time_req,
				&set2,
				cred_usage,
				&mc->gmc_cred,
				NULL,
				NULL);
    } else if (credential_type == GSS_C_NO_OID) {
	major_status = m->gm_acquire_cred(minor_status,
					  mn->gmn_name,
					  time_req,
					  &set2,
					  cred_usage,
					  &mc->gmc_cred,
					  NULL,
					  NULL);
    } else {
	major_status = GSS_S_UNAVAILABLE;
	free(mc);
	mc= NULL;
    }

    *output_cred_handle = mc;
    return major_status;
}