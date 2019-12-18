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
struct parse {size_t nargs; TYPE_1__* argval; } ;
struct conf_sys_flags {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {char* string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 int INFO_ERR_IMPL ; 
 scalar_t__ STREQ (char*,char*) ; 
 int /*<<< orphan*/  SYS_FLAG_AUTH ; 
 int /*<<< orphan*/  SYS_FLAG_BCLIENT ; 
 int /*<<< orphan*/  SYS_FLAG_CAL ; 
 int /*<<< orphan*/  SYS_FLAG_FILEGEN ; 
 int /*<<< orphan*/  SYS_FLAG_KERNEL ; 
 int /*<<< orphan*/  SYS_FLAG_MONITOR ; 
 int /*<<< orphan*/  SYS_FLAG_NTP ; 
 int /*<<< orphan*/  SYS_FLAG_PPS ; 
 int doquery (scalar_t__,int,int,int,int,char*,size_t*,size_t*,char const**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ impl_ver ; 

__attribute__((used)) static void
doset(
	struct parse *pcmd,
	FILE *fp,
	int req
	)
{
	struct conf_sys_flags sys;
	size_t items;
	size_t itemsize;
	const char *dummy;
	int res;

	sys.flags = 0;
	res = 0;
	for (items = 0; (size_t)items < pcmd->nargs; items++) {
		if (STREQ(pcmd->argval[items].string, "auth"))
			sys.flags |= SYS_FLAG_AUTH;
		else if (STREQ(pcmd->argval[items].string, "bclient"))
			sys.flags |= SYS_FLAG_BCLIENT;
		else if (STREQ(pcmd->argval[items].string, "calibrate"))
			sys.flags |= SYS_FLAG_CAL;
		else if (STREQ(pcmd->argval[items].string, "kernel"))
			sys.flags |= SYS_FLAG_KERNEL;
		else if (STREQ(pcmd->argval[items].string, "monitor"))
			sys.flags |= SYS_FLAG_MONITOR;
		else if (STREQ(pcmd->argval[items].string, "ntp"))
			sys.flags |= SYS_FLAG_NTP;
		else if (STREQ(pcmd->argval[items].string, "pps"))
			sys.flags |= SYS_FLAG_PPS;
		else if (STREQ(pcmd->argval[items].string, "stats"))
			sys.flags |= SYS_FLAG_FILEGEN;
		else {
			(void) fprintf(fp, "Unknown flag %s\n",
			    pcmd->argval[items].string);
			res = 1;
		}
	}

	sys.flags = htonl(sys.flags);
	if (res || sys.flags == 0)
	    return;

again:
	res = doquery(impl_ver, req, 1, 1,
		      sizeof(struct conf_sys_flags), (char *)&sys, &items,
		      &itemsize, &dummy, 0, sizeof(struct conf_sys_flags));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res == 0)
	    (void) fprintf(fp, "done!\n");
}