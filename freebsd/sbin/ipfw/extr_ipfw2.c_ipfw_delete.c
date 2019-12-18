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
typedef  int /*<<< orphan*/  rt ;
struct TYPE_5__ {int set; int start_rule; int end_rule; scalar_t__ new_set; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ipfw_range_tlv ;
struct TYPE_6__ {int use_set; int do_dynamic; scalar_t__ do_force; scalar_t__ do_quiet; scalar_t__ do_pipe; scalar_t__ do_nat; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int EX_OK ; 
 int EX_UNAVAILABLE ; 
 int /*<<< orphan*/  IPFW_RCFLAG_ALL ; 
 int /*<<< orphan*/  IPFW_RCFLAG_DYNAMIC ; 
 int /*<<< orphan*/  IPFW_RCFLAG_RANGE ; 
 int /*<<< orphan*/  IPFW_RCFLAG_SET ; 
 int /*<<< orphan*/  IP_FW_NAT_DEL ; 
 int /*<<< orphan*/  IP_FW_XDEL ; 
 int /*<<< orphan*/  NEED1 (char*) ; 
 scalar_t__ _substrcmp (char*,char*) ; 
 TYPE_4__ co ; 
 int do_cmd (int /*<<< orphan*/ ,int*,int) ; 
 int do_range_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int ipfw_delete_pipe (scalar_t__,int) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  warn (char*,int) ; 
 int /*<<< orphan*/  warnx (char*,int,...) ; 

void
ipfw_delete(char *av[])
{
	ipfw_range_tlv rt;
	char *sep;
	int i, j;
	int exitval = EX_OK;
	int do_set = 0;

	av++;
	NEED1("missing rule specification");
	if ( *av && _substrcmp(*av, "set") == 0) {
		/* Do not allow using the following syntax:
		 *	ipfw set N delete set M
		 */
		if (co.use_set)
			errx(EX_DATAERR, "invalid syntax");
		do_set = 1;	/* delete set */
		av++;
	}

	/* Rule number */
	while (*av && isdigit(**av)) {
		i = strtol(*av, &sep, 10);
		j = i;
		if (*sep== '-')
			j = strtol(sep + 1, NULL, 10);
		av++;
		if (co.do_nat) {
			exitval = do_cmd(IP_FW_NAT_DEL, &i, sizeof i);
			if (exitval) {
				exitval = EX_UNAVAILABLE;
				if (co.do_quiet)
					continue;
				warn("nat %u not available", i);
			}
		} else if (co.do_pipe) {
			exitval = ipfw_delete_pipe(co.do_pipe, i);
		} else {
			memset(&rt, 0, sizeof(rt));
			if (do_set != 0) {
				rt.set = i & 31;
				rt.flags = IPFW_RCFLAG_SET;
			} else {
				rt.start_rule = i & 0xffff;
				rt.end_rule = j & 0xffff;
				if (rt.start_rule == 0 && rt.end_rule == 0)
					rt.flags |= IPFW_RCFLAG_ALL;
				else
					rt.flags |= IPFW_RCFLAG_RANGE;
				if (co.use_set != 0) {
					rt.set = co.use_set - 1;
					rt.flags |= IPFW_RCFLAG_SET;
				}
			}
			if (co.do_dynamic == 2)
				rt.flags |= IPFW_RCFLAG_DYNAMIC;
			i = do_range_cmd(IP_FW_XDEL, &rt);
			if (i != 0) {
				exitval = EX_UNAVAILABLE;
				if (co.do_quiet)
					continue;
				warn("rule %u: setsockopt(IP_FW_XDEL)",
				    rt.start_rule);
			} else if (rt.new_set == 0 && do_set == 0 &&
			    co.do_dynamic != 2) {
				exitval = EX_UNAVAILABLE;
				if (co.do_quiet)
					continue;
				if (rt.start_rule != rt.end_rule)
					warnx("no rules rules in %u-%u range",
					    rt.start_rule, rt.end_rule);
				else
					warnx("rule %u not found",
					    rt.start_rule);
			}
		}
	}
	if (exitval != EX_OK && co.do_force == 0)
		exit(exitval);
}