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
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RPC_GSS_ER_SYSTEMERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _rpc_gss_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kgss_find_mech_by_oid (int /*<<< orphan*/ ) ; 

bool_t
rpc_gss_oid_to_mech(gss_OID oid, const char **mech_ret)
{
	const char *name = kgss_find_mech_by_oid(oid);

	if (name) {
		*mech_ret = name;
		return (TRUE);
	}
	_rpc_gss_set_error(RPC_GSS_ER_SYSTEMERROR, ENOENT);
	return (FALSE);
}