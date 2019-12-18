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
struct _gss_mechanism_cred {int /*<<< orphan*/  gmc_cred; int /*<<< orphan*/ * gmc_mech_oid; struct _gss_mech_switch* gmc_mech; } ;
struct _gss_mech_switch {int /*<<< orphan*/  gm_mech_oid; int /*<<< orphan*/  (* gm_release_cred ) (scalar_t__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* gm_release_name ) (scalar_t__*,int /*<<< orphan*/ *) ;scalar_t__ (* gm_add_cred ) (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* gm_inquire_cred_by_mech ) (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  int /*<<< orphan*/  gss_cred_usage_t ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_CREDENTIAL ; 
 int /*<<< orphan*/  _gss_mg_error (struct _gss_mech_switch*,scalar_t__,scalar_t__) ; 
 struct _gss_mechanism_cred* malloc (int) ; 
 scalar_t__ stub1 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct _gss_mechanism_cred *
_gss_copy_cred(struct _gss_mechanism_cred *mc)
{
	struct _gss_mechanism_cred *new_mc;
	struct _gss_mech_switch *m = mc->gmc_mech;
	OM_uint32 major_status, minor_status;
	gss_name_t name;
	gss_cred_id_t cred;
	OM_uint32 initiator_lifetime, acceptor_lifetime;
	gss_cred_usage_t cred_usage;

	major_status = m->gm_inquire_cred_by_mech(&minor_status,
	    mc->gmc_cred, mc->gmc_mech_oid,
	    &name, &initiator_lifetime, &acceptor_lifetime, &cred_usage);
	if (major_status) {
		_gss_mg_error(m, major_status, minor_status);
		return (0);
	}

	major_status = m->gm_add_cred(&minor_status,
	    GSS_C_NO_CREDENTIAL, name, mc->gmc_mech_oid,
	    cred_usage, initiator_lifetime, acceptor_lifetime,
	    &cred, 0, 0, 0);
	m->gm_release_name(&minor_status, &name);

	if (major_status) {
		_gss_mg_error(m, major_status, minor_status);
		return (0);
	}

	new_mc = malloc(sizeof(struct _gss_mechanism_cred));
	if (!new_mc) {
		m->gm_release_cred(&minor_status, &cred);
		return (0);
	}
	new_mc->gmc_mech = m;
	new_mc->gmc_mech_oid = &m->gm_mech_oid;
	new_mc->gmc_cred = cred;

	return (new_mc);
}