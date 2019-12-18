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
typedef  int /*<<< orphan*/  s_i ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  i ;
typedef  enum snmp_op { ____Placeholder_snmp_op } snmp_op ;
struct TYPE_2__ {int val; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int LEAF_begemotBridgeLayer2PfStatus ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_OP_SET ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* bridge_pf_sysctl ; 
 int /*<<< orphan*/  bridge_sysctl ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int sysctlbyname (char*,int*,size_t*,int*,size_t) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

int32_t
bridge_do_pfctl(int32_t bridge_ctl, enum snmp_op op, int32_t *val)
{
	char *mib_oid;
	size_t len, s_len;
	int32_t i, s_i;

	if (bridge_ctl >= LEAF_begemotBridgeLayer2PfStatus)
		return (-2);

	if (op == SNMP_OP_SET) {
		s_i = *val;
		s_len = sizeof(s_i);
	} else
		s_len = 0;

	len = sizeof(i);

	asprintf(&mib_oid, "%s%s", bridge_sysctl,
	    bridge_pf_sysctl[bridge_ctl].name);
	if (mib_oid == NULL)
		return (-1);

	if (sysctlbyname(mib_oid, &i, &len, (op == SNMP_OP_SET ? &s_i : NULL),
	    s_len) == -1) {
		syslog(LOG_ERR, "sysctl(%s) failed - %s", mib_oid,
		    strerror(errno));
		free(mib_oid);
		return (-1);
	}

	bridge_pf_sysctl[bridge_ctl].val = i;
	*val = i;

	free(mib_oid);

	return (i);
}