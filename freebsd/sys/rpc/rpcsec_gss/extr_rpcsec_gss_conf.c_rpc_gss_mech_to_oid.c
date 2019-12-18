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
typedef  scalar_t__ gss_OID ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RPC_GSS_ER_SYSTEMERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _rpc_gss_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kgss_find_mech_by_name (char const*) ; 

bool_t
rpc_gss_mech_to_oid(const char *mech, gss_OID *oid_ret)
{
	gss_OID oid = kgss_find_mech_by_name(mech);

	if (oid) {
		*oid_ret = oid;
		return (TRUE);
	}
	_rpc_gss_set_error(RPC_GSS_ER_SYSTEMERROR, ENOENT);
	return (FALSE);
}