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
struct snmp_toolinfo {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IsoOrgDod_OID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_flist (struct snmp_toolinfo*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t
parse_file(struct snmp_toolinfo *snmptoolctx, char *opt_arg)
{
	assert(opt_arg != NULL);

	if (parse_flist(snmptoolctx, opt_arg, NULL, &IsoOrgDod_OID) < 0)
		return (-1);

	return (2);
}