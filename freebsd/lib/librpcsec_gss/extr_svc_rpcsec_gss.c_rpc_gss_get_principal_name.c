#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rpc_gss_principal_t ;
typedef  int /*<<< orphan*/  gss_name_t ;
struct TYPE_8__ {size_t length; void* value; } ;
typedef  TYPE_2__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_7__ {int len; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GSS_C_NT_USER_NAME ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gss_canonicalize_name (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_export_name (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ gss_import_name (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_2__*) ; 
 int /*<<< orphan*/  gss_release_name (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_status (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 void* mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (void*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  rpc_gss_mech_to_oid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svc_rpc_gss_init () ; 

bool_t
rpc_gss_get_principal_name(rpc_gss_principal_t *principal,
    const char *mech, const char *name, const char *node, const char *domain)
{
	OM_uint32		maj_stat, min_stat;
	gss_OID			mech_oid;
	size_t			namelen;
	gss_buffer_desc		buf;
	gss_name_t		gss_name, gss_mech_name;
	rpc_gss_principal_t	result;

	svc_rpc_gss_init();

	if (!rpc_gss_mech_to_oid(mech, &mech_oid))
		return (FALSE);

	/*
	 * Construct a gss_buffer containing the full name formatted
	 * as "name/node@domain" where node and domain are optional.
	 */
	namelen = strlen(name);
	if (node) {
		namelen += strlen(node) + 1;
	}
	if (domain) {
		namelen += strlen(domain) + 1;
	}

	buf.value = mem_alloc(namelen);
	buf.length = namelen;
	strcpy((char *) buf.value, name);
	if (node) {
		strcat((char *) buf.value, "/");
		strcat((char *) buf.value, node);
	}
	if (domain) {
		strcat((char *) buf.value, "@");
		strcat((char *) buf.value, domain);
	}

	/*
	 * Convert that to a gss_name_t and then convert that to a
	 * mechanism name in the selected mechanism.
	 */
	maj_stat = gss_import_name(&min_stat, &buf,
	    GSS_C_NT_USER_NAME, &gss_name);
	mem_free(buf.value, buf.length);
	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_import_name", mech_oid, maj_stat, min_stat);
		return (FALSE);
	}
	maj_stat = gss_canonicalize_name(&min_stat, gss_name, mech_oid,
	    &gss_mech_name);
	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_canonicalize_name", mech_oid, maj_stat,
		    min_stat);
		gss_release_name(&min_stat, &gss_name);
		return (FALSE);
	}
	gss_release_name(&min_stat, &gss_name);

	/*
	 * Export the mechanism name and use that to construct the
	 * rpc_gss_principal_t result.
	 */
	maj_stat = gss_export_name(&min_stat, gss_mech_name, &buf);
	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_export_name", mech_oid, maj_stat, min_stat);
		gss_release_name(&min_stat, &gss_mech_name);
		return (FALSE);
	}
	gss_release_name(&min_stat, &gss_mech_name);

	result = mem_alloc(sizeof(int) + buf.length);
	if (!result) {
		gss_release_buffer(&min_stat, &buf);
		return (FALSE);
	}
	result->len = buf.length;
	memcpy(result->name, buf.value, buf.length);
	gss_release_buffer(&min_stat, &buf);

	*principal = result;
	return (TRUE);
}