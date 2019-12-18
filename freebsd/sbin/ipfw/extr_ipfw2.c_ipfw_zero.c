#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  rt ;
struct TYPE_5__ {int start_rule; int end_rule; scalar_t__ set; scalar_t__ new_set; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ipfw_range_tlv ;
struct TYPE_6__ {scalar_t__ use_set; int /*<<< orphan*/  do_quiet; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int EX_OK ; 
 int EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IPFW_RCFLAG_ALL ; 
 int /*<<< orphan*/  IPFW_RCFLAG_RANGE ; 
 int /*<<< orphan*/  IPFW_RCFLAG_SET ; 
 int IP_FW_XRESETLOG ; 
 int IP_FW_XZERO ; 
 TYPE_4__ co ; 
 scalar_t__ do_range_cmd (int,TYPE_1__*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strtonum (char*,int /*<<< orphan*/ ,int,char const**) ; 
 int /*<<< orphan*/  warn (char*,int,char const*) ; 

void
ipfw_zero(int ac, char *av[], int optname)
{
	ipfw_range_tlv rt;
	char const *errstr;
	char const *name = optname ? "RESETLOG" : "ZERO";
	uint32_t arg;
	int failed = EX_OK;

	optname = optname ? IP_FW_XRESETLOG : IP_FW_XZERO;
	av++; ac--;

	if (ac == 0) {
		/* clear all entries */
		memset(&rt, 0, sizeof(rt));
		rt.flags = IPFW_RCFLAG_ALL;
		if (do_range_cmd(optname, &rt) < 0)
			err(EX_UNAVAILABLE, "setsockopt(IP_FW_X%s)", name);
		if (!co.do_quiet)
			printf("%s.\n", optname == IP_FW_XZERO ?
			    "Accounting cleared":"Logging counts reset");

		return;
	}

	while (ac) {
		/* Rule number */
		if (isdigit(**av)) {
			arg = strtonum(*av, 0, 0xffff, &errstr);
			if (errstr)
				errx(EX_DATAERR,
				    "invalid rule number %s\n", *av);
			memset(&rt, 0, sizeof(rt));
			rt.start_rule = arg;
			rt.end_rule = arg;
			rt.flags |= IPFW_RCFLAG_RANGE;
			if (co.use_set != 0) {
				rt.set = co.use_set - 1;
				rt.flags |= IPFW_RCFLAG_SET;
			}
			if (do_range_cmd(optname, &rt) != 0) {
				warn("rule %u: setsockopt(IP_FW_X%s)",
				    arg, name);
				failed = EX_UNAVAILABLE;
			} else if (rt.new_set == 0) {
				printf("Entry %d not found\n", arg);
				failed = EX_UNAVAILABLE;
			} else if (!co.do_quiet)
				printf("Entry %d %s.\n", arg,
				    optname == IP_FW_XZERO ?
					"cleared" : "logging count reset");
		} else {
			errx(EX_USAGE, "invalid rule number ``%s''", *av);
		}
		av++; ac--;
	}
	if (failed != EX_OK)
		exit(failed);
}