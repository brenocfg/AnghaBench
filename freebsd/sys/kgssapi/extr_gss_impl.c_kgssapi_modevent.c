#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_2__ {int /*<<< orphan*/  rpc_gss_svc_max_data_length; int /*<<< orphan*/  rpc_gss_get_principal_name; int /*<<< orphan*/  rpc_gss_clear_callback; int /*<<< orphan*/  rpc_gss_set_callback; int /*<<< orphan*/  rpc_gss_getcred; int /*<<< orphan*/  rpc_gss_clear_svc_name; int /*<<< orphan*/  rpc_gss_set_svc_name; int /*<<< orphan*/  rpc_gss_is_installed; int /*<<< orphan*/  rpc_gss_get_versions; int /*<<< orphan*/  rpc_gss_get_mechanisms; int /*<<< orphan*/  rpc_gss_qop_to_num; int /*<<< orphan*/  rpc_gss_oid_to_mech; int /*<<< orphan*/  rpc_gss_mech_to_oid; int /*<<< orphan*/  rpc_gss_get_error; int /*<<< orphan*/  rpc_gss_max_data_length; int /*<<< orphan*/  rpc_gss_set_defaults; int /*<<< orphan*/  rpc_gss_seccreate; int /*<<< orphan*/  rpc_gss_secpurge; int /*<<< orphan*/  rpc_gss_secfind; int /*<<< orphan*/  rpc_gss_refresh_auth; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  kgss_gssd_lock ; 
 int kgss_load () ; 
 int /*<<< orphan*/  kgss_unload () ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_gss_clear_callback ; 
 int /*<<< orphan*/  rpc_gss_clear_svc_name ; 
 TYPE_1__ rpc_gss_entries ; 
 int /*<<< orphan*/  rpc_gss_get_error ; 
 int /*<<< orphan*/  rpc_gss_get_mechanisms ; 
 int /*<<< orphan*/  rpc_gss_get_principal_name ; 
 int /*<<< orphan*/  rpc_gss_get_versions ; 
 int /*<<< orphan*/  rpc_gss_getcred ; 
 int /*<<< orphan*/  rpc_gss_is_installed ; 
 int /*<<< orphan*/  rpc_gss_max_data_length ; 
 int /*<<< orphan*/  rpc_gss_mech_to_oid ; 
 int /*<<< orphan*/  rpc_gss_oid_to_mech ; 
 int /*<<< orphan*/  rpc_gss_qop_to_num ; 
 int /*<<< orphan*/  rpc_gss_refresh_auth ; 
 int /*<<< orphan*/  rpc_gss_seccreate ; 
 int /*<<< orphan*/  rpc_gss_secfind ; 
 int /*<<< orphan*/  rpc_gss_secpurge ; 
 int /*<<< orphan*/  rpc_gss_set_callback ; 
 int /*<<< orphan*/  rpc_gss_set_defaults ; 
 int /*<<< orphan*/  rpc_gss_set_svc_name ; 
 int /*<<< orphan*/  rpc_gss_svc_max_data_length ; 

__attribute__((used)) static int
kgssapi_modevent(module_t mod, int type, void *data)
{
	int error = 0;

	switch (type) {
	case MOD_LOAD:
		rpc_gss_entries.rpc_gss_refresh_auth = rpc_gss_refresh_auth;
		rpc_gss_entries.rpc_gss_secfind = rpc_gss_secfind;
		rpc_gss_entries.rpc_gss_secpurge = rpc_gss_secpurge;
		rpc_gss_entries.rpc_gss_seccreate = rpc_gss_seccreate;
		rpc_gss_entries.rpc_gss_set_defaults = rpc_gss_set_defaults;
		rpc_gss_entries.rpc_gss_max_data_length =
		    rpc_gss_max_data_length;
		rpc_gss_entries.rpc_gss_get_error = rpc_gss_get_error;
		rpc_gss_entries.rpc_gss_mech_to_oid = rpc_gss_mech_to_oid;
		rpc_gss_entries.rpc_gss_oid_to_mech = rpc_gss_oid_to_mech;
		rpc_gss_entries.rpc_gss_qop_to_num = rpc_gss_qop_to_num;
		rpc_gss_entries.rpc_gss_get_mechanisms = rpc_gss_get_mechanisms;
		rpc_gss_entries.rpc_gss_get_versions = rpc_gss_get_versions;
		rpc_gss_entries.rpc_gss_is_installed = rpc_gss_is_installed;
		rpc_gss_entries.rpc_gss_set_svc_name = rpc_gss_set_svc_name;
		rpc_gss_entries.rpc_gss_clear_svc_name = rpc_gss_clear_svc_name;
		rpc_gss_entries.rpc_gss_getcred = rpc_gss_getcred;
		rpc_gss_entries.rpc_gss_set_callback = rpc_gss_set_callback;
		rpc_gss_entries.rpc_gss_clear_callback = rpc_gss_clear_callback;
		rpc_gss_entries.rpc_gss_get_principal_name =
		    rpc_gss_get_principal_name;
		rpc_gss_entries.rpc_gss_svc_max_data_length =
		    rpc_gss_svc_max_data_length;
		mtx_init(&kgss_gssd_lock, "kgss_gssd_lock", NULL, MTX_DEF);
		error = kgss_load();
		break;
	case MOD_UNLOAD:
		kgss_unload();
		mtx_destroy(&kgss_gssd_lock);
		/*
		 * Unloading of the kgssapi module is not currently supported.
		 * If somebody wants this, we would need to keep track of
		 * currently executing threads and make sure the count is 0.
		 */
		/* FALLTHROUGH */
	default:
		error = EOPNOTSUPP;
	}
	return (error);
}